//
// BomberGame.cpp for BomberGame.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Sun Jun  8 16:37:06 2014 CHAUCHET Alan
// Last update Mon Nov 10 17:22:41 2014 abgral_f
//

#include		"Game/BomberGame.hh"
#include		"Game/Player.hh"
#include		"Game/IA.hh"
#include		"Game/Key.hh"
#include		"Game/LexerSave.hh"
#include		"Game/ParserSave.hh"
#include		"Game/LexerScore.hh"
#include		"Game/ParserScore.hh"
#include		"GUI/Window.hh"
#include		"GUI/MapGUI.hh"
#include		"GUI/MenuGUI.hh"
#include		"GUI/Cinematic.hh"
#include		"GUI/Sound.hh"

BomberGame::BomberGame()
{
  this->_isPlayer2 = false;
  this->_condPlayer1.create();
  this->_condPlayer2.create();
  this->_mutexPlayer1.create();
  this->_mutexPlayer2.create();
  this->_condBomb.create();
  this->_map = NULL;
  Key::initBasicKey();
  Key::parseKeyFile();
  this->_quit = false;
  this->_window = new Window(this);
  this->_menuGUI = new MenuGUI(this->_window);
  this->_mapGUI = new MapGUI(this->_window);
  this->_cinematic = new Cinematic(this->_window);
  this->_isPaused = false;

  Sound::initialize();

  Sound::addMusic("music_menu.mp3", MUSIC_MENU);
  Sound::addMusic("music_game.mp3", MUSIC_GAME);
  Sound::addMusic("music_win.mp3", MUSIC_WIN);
  Sound::addMusic("music_lose.mp3", MUSIC_LOSE);

  Sound::addSound("sound_menu.wav", SOUND_MENU);
  Sound::addSound("sound_move.wav", SOUND_MOVE);
  Sound::addSound("sound_drop.wav", SOUND_PUT_BOMB);
  Sound::addSound("sound_blow.wav", SOUND_EXPLOSE);
  Sound::addSound("sound_bonus.wav", SOUND_BONUS);
  Sound::addSound("sound_pause.wav", SOUND_PAUSE);
  Sound::addSound("sound_die.wav", SOUND_DIE);
  Sound::addSound("sound_error.wav", SOUND_ERROR);

  Sound::setVolumeMusic(50);
  Sound::setVolumeSound(50);
}

BomberGame::~BomberGame()
{
  Sound::close();
  Key::writeKeyFile();
  this->_condPlayer1.destroy();
  this->_condPlayer2.destroy();
  this->_mutexPlayer1.destroy();
  this->_mutexPlayer2.destroy();
  this->_condBomb.destroy();
  if (this->_map)
    delete (this->_map);
  this->_window->stop();
  delete(this->_cinematic);
  delete(this->_menuGUI);
  delete(this->_mapGUI);
  delete(this->_window);
}

void			BomberGame::createMap(unsigned int x, unsigned int y)
{
  if (this->_map)
    delete (this->_map);
  this->_map = new Map(x, y);
}

void			BomberGame::createMap(unsigned int x, unsigned int y, const std::vector<Box *> &boxs)
{
  if (this->_map)
    delete (this->_map);
  this->_map = new Map(x, y, boxs);
}

void			BomberGame::addActionPlayer1(e_action action)
{
  if (this->_isPaused)
    return ;
  this->_mutexPlayer1.lock();
  this->_actionPlayer1.push_back(action);
  this->_mutexPlayer1.unlock();
}

void			BomberGame::addActionPlayer2(e_action action)
{
  if (this->_isPaused)
    return ;
  this->_mutexPlayer2.lock();
  this->_actionPlayer2.push_back(action);
  this->_mutexPlayer2.unlock();
}

bool			BomberGame::takeActionPlayer1(e_action &action)
{
  if (this->_isPaused)
    return (false);
  this->_mutexPlayer1.lock();
  if (this->_actionPlayer1.size() == 0)
    {
      this->_mutexPlayer1.unlock();
      return (false);
       }
  action = this->_actionPlayer1[0];
  this->_actionPlayer1.erase(this->_actionPlayer1.begin());
  this->_mutexPlayer1.unlock();
  return (true);
}

void			BomberGame::setAnim(bool change)
{
  this->_anim = change;
}

bool			BomberGame::getAnim(void) const
{
  return (this->_anim);
}

bool			BomberGame::takeActionPlayer2(e_action &action)
{
  if (this->_isPaused)
    return (false);
  this->_mutexPlayer2.lock();
  if (this->_actionPlayer2.size() == 0)
    {
      this->_mutexPlayer2.unlock();
      return (false);
    }
  action = this->_actionPlayer2[0];
  this->_actionPlayer2.erase(this->_actionPlayer2.begin());
  this->_mutexPlayer2.unlock();
  return (true);
}

void			BomberGame::emptyActionPlayer1(void)
{
  this->_mutexPlayer1.lock();
  this->_actionPlayer1.clear();
  this->_mutexPlayer1.unlock();
}

void			BomberGame::emptyActionPlayer2(void)
{
  this->_mutexPlayer2.lock();
  this->_actionPlayer2.clear();
  this->_mutexPlayer2.unlock();
}

Cond			*BomberGame::getCondAction(e_playerType type)
{
  if (type == PLAYER1)
    return (&(this->_condPlayer1));
  return (&(this->_condPlayer2));
}

Map			*BomberGame::getMap(void)
{
  return (this->_map);
}

Cond			*BomberGame::getCondBomb(void)
{
  return (&(this->_condBomb));
}

bool			BomberGame::getIsPlayer2(void) const {
  return (this->_isPlayer2);
}

void			BomberGame::setIsPlayer2(bool isPlayer2) {
  this->_isPlayer2 = isPlayer2;
}

void			BomberGame::createPlayers(bool isPlayer2, unsigned int nbIA, int difficulty)
{
  unsigned int		nbPlayer = nbIA + ((isPlayer2 == true) ? 2 : 1);
  unsigned int		decal = (this->_map->getSizeX() - 2) * (this->_map->getSizeY() - 2) / nbPlayer;
  unsigned int		x = 0;

  this->_players.push_back(new Player(this, PLAYER1, x % (this->_map->getSizeX() - 2) + 1, x / (this->_map->getSizeX() - 2) + 1));
  x += decal;
  for (unsigned int count = 0; count < nbIA; ++count) {
    this->_players.push_back(new IA(this, x % (this->_map->getSizeX() - 2) + 1, x / (this->_map->getSizeX() - 2) + 1, difficulty, &(this->_players)));
    x += decal;
  }
  if (isPlayer2) {
    this->_isPlayer2 = true;
    this->_players.push_back(new Player(this, PLAYER2, x % (this->_map->getSizeX() - 2) + 1, x / (this->_map->getSizeX() - 2) + 1));
  }
}

void			BomberGame::createPlayersLoadMap(bool isPlayer2, unsigned int nbIA, int difficulty)
{
  unsigned int		nbPlayer = nbIA + ((isPlayer2 == true) ? 2 : 1);
  unsigned int		maxPlayer = nbPlayer;
  unsigned int		side, coordx, coordy;
  unsigned int		nbSpot = 0;
  unsigned int		tmpSpot = 0;

  for (unsigned int x = 0; nbPlayer > 0 && x < (this->_map->getSizeX() - 2) * (this->_map->getSizeY() - 2); ++x)
    {
      coordx = x % (this->_map->getSizeX() - 2) + 1;
      coordy = x / (this->_map->getSizeX() - 2) + 1;
      if (!_map->isObstacle(coordx, coordy))
	{

	  side = 0;
	  if (!_map->isObstacle(coordx + 1, coordy))
	    ++side;
	  if (!_map->isObstacle(coordx - 1, coordy))
	    ++side;
	  if (!_map->isObstacle(coordx, coordy + 1))
	    ++side;
	  if (!_map->isObstacle(coordx, coordy - 1))
	    ++side;
	  if (side >= 2)
	    ++nbSpot;

	}
    }
  if (nbSpot == 0)
    return ;
  nbSpot = nbSpot / nbPlayer;

  while (nbPlayer > 0)
    {
      for (unsigned int x = 0; nbPlayer > 0 && x < (this->_map->getSizeX() - 2) * (this->_map->getSizeY() - 2); ++x)
	{
	  coordx = x % (this->_map->getSizeX() - 2) + 1;
	  coordy = x / (this->_map->getSizeX() - 2) + 1;
	  if (!_map->isObstacle(coordx, coordy))
	    {

	      side = 0;
	      if (!_map->isObstacle(coordx + 1, coordy))
		++side;
	      if (!_map->isObstacle(coordx - 1, coordy))
		++side;
	      if (!_map->isObstacle(coordx, coordy + 1))
		++side;
	      if (!_map->isObstacle(coordx, coordy - 1))
		++side;
	      if (side >= 2)

		{
		  ++tmpSpot;
		  if (tmpSpot >= nbSpot)
		    {
		      tmpSpot = 0;
		      if (nbPlayer == maxPlayer)
			this->_players.push_back(new Player(this, PLAYER1, coordx, coordy));
		      else if (nbPlayer == 1 && isPlayer2)
			this->_players.push_back(new Player(this, PLAYER2, coordx, coordy));
		      else
			this->_players.push_back(new IA(this, coordx, coordy, difficulty, &(this->_players)));
		      --nbPlayer;
		    }
		}

	    }
	}
    }
  if (isPlayer2)
    this->_isPlayer2 = true;
}

void			BomberGame::launchPlayers(void) const
{
  for (unsigned int count = 0; count < this->_players.size(); count++)
    this->_players[count]->launch();
}

std::vector<APlayer *>	*BomberGame::getPlayersAccess(void)
{
  return (&(this->_players));
}

void			BomberGame::save(const std::string &fileName)
{
  std::vector<std::string> param;
  ParserSave		parser(param, this);

  parser.writeInFile(this->_map, this->_players, "./.Save/" + fileName);
}

void			BomberGame::load(const std::string &fileName, bool isSave)
{
  LexerSave		lexer;

  if (isSave)
    lexer.checkFile("./.Save/" + fileName);
  else
    lexer.checkFile("./.Map/" + fileName);

  ParserSave		parser(lexer.getLines(), this);

  try
    {
      parser.parseFile();
      this->_map = parser.getMap();
      this->_players = parser.getPlayers();
      for (unsigned int count = 0; count < this->_players.size(); ++count)
	{
	  this->_players[count]->setMap(this->_map);
	  if (this->_players[count]->getType() == PLAYER2)
	    this->_isPlayer2 = true;
	}
    }
  catch (const std::invalid_argument &err)
    {
      parser.clear();
      throw;
    }
}

void			BomberGame::fillMap(void) const
{
  this->_map->fillMap(this->_players);
}

void			BomberGame::pause(void)
{
  this->_isPaused = true;
  Sound::pauseSound();
  Sound::pauseMusic();
  for (unsigned int count = 0; count < this->_players.size(); count++)
    this->_players[count]->pauseBombs();
  this->_menuGUI->initialize();
  this->_menuGUI->getMenu().setPause(true);
  this->_menuGUI->getMenu().createPause();
  while (this->_isPaused == true && this->_stop == false && this->_menuGUI->update())
    {
      this->_menuGUI->draw();
      if (this->_menuGUI->getMenu().getIsBackup() == true)
	{
	  this->save(this->_menuGUI->getMenu().getBackup());
          this->_menuGUI->getMenu().setIsBackup(false);
	}
      if (this->_menuGUI->getMenu().getPause() == false)
	{
	  glEnable(GL_DEPTH_TEST);
	  this->unpause();
	  this->_mapGUI->draw();
	}
      if (this->_menuGUI->getMenu().getQuit())
	{
	  this->_menuGUI->getMenu().setQuit(false);
	  this->_stop = true;
	  this->unpause();
	}
    }
}

void			BomberGame::unpause(void)
{
  this->_isPaused = false;
  Sound::unpauseSound();
  Sound::unpauseMusic();
  for (unsigned int count = 0; count < this->_players.size(); count++)
    this->_players[count]->unpauseBombs();
}

void			BomberGame::setQuit(bool quit)
{
  this->_quit = quit;
}

void			BomberGame::start(void)
{
  bool			isOk;
  unsigned int		x;
  unsigned int		y;
  bool			twoPlayers;
  unsigned int		nbIa;
  int			difficulty;

  this->_window->initialize();
  if (this->_anim == true)
    {
      this->_cinematic->initialize();
      while (this->_cinematic->update() && !this->_quit)
	this->_cinematic->draw();
    }
  while (!this->_quit)
    {
      isOk = true;
      if (!this->_menuGUI->initialize())
	this->_quit = true;
      else
	{
	  Sound::playMusic(MUSIC_MENU, -1);
	  while (!this->_quit && this->_menuGUI->update() &&
		 !this->_menuGUI->getMenu().getPlay())
	    {
	      if (this->_menuGUI->getMenu().getQuit())
		this->_quit = true;
	      this->_menuGUI->draw();
	    }
	  if (this->_menuGUI->getMenu().getPlay())
	    {
	      if (this->_menuGUI->getMenu().getLoadGame().size())
		{
		  try
		    {
		      this->load(this->_menuGUI->getMenu().getLoadGame());
		    }
		  catch (const std::invalid_argument &err)
		    {
		      this->affError("save corrupted", isOk);
		    }
		}
	      else
		{
		  if (this->_menuGUI->getMenu().getMapChoosen().size())
		    {
		      try
			{
			  this->load(this->_menuGUI->getMenu().getMapChoosen(), false);
			}
		      catch (const std::invalid_argument &err)
			{
			  this->affError("map corrupted", isOk);
			}
		      if (isOk)
			{
			  twoPlayers = this->_menuGUI->getMenu().getTwoPlayers();
			  nbIa = this->_menuGUI->getMenu().getNbIaPlayers();
			  difficulty = this->_menuGUI->getMenu().getIaDifficulty();
			  if (twoPlayers == false && nbIa == 0)
			    this->affError("not enough players", isOk);
			  else if (this->_map->getSizeX() * this->_map->getSizeY() < nbIa + 1 + static_cast<int>(twoPlayers))
			    this->affError("too many players for the map", isOk);
			  else
			    {
			      this->createPlayersLoadMap(twoPlayers, nbIa, difficulty);
			      this->getPlayer(PLAYER1)->setName(this->_menuGUI->getMenu().getNamePlayer1());
			      if (twoPlayers)
				this->getPlayer(PLAYER2)->setName(this->_menuGUI->getMenu().getNamePlayer2());
			    }
			}
		    }
		  else
		    {
		      x = this->_menuGUI->getMenu().getMapLenght();
		      y = this->_menuGUI->getMenu().getMapWidth();
		      twoPlayers = this->_menuGUI->getMenu().getTwoPlayers();
		      nbIa = this->_menuGUI->getMenu().getNbIaPlayers();
		      difficulty = this->_menuGUI->getMenu().getIaDifficulty();
		      if (twoPlayers == false && nbIa == 0)
			this->affError("not enough players", isOk);
		      else if (x * y < nbIa + 1 + static_cast<int>(twoPlayers))
			this->affError("too many players for the map", isOk);
		      else
			{
			  this->createMap(x, y);
			  this->createPlayers(twoPlayers, nbIa, difficulty);
			  this->getPlayer(PLAYER1)->setName(this->_menuGUI->getMenu().getNamePlayer1());
			  if (twoPlayers)
			    this->getPlayer(PLAYER2)->setName(this->_menuGUI->getMenu().getNamePlayer2());
			  this->fillMap();
			}
		    }
		}
	      if (isOk)
		{
		  this->play();
		  if (this->_winner != NOBODY)
		    {
		      if (this->_winner == PLAYER1_WIN)
			Sound::playMusic(MUSIC_WIN, 0);
		      else
			Sound::playMusic(MUSIC_LOSE, 0);
		      this->_menuGUI->initialize();
		      this->_menuGUI->getMenu().createResults(this->_scoreNames,
							      this->_scoreValues, this->_winnerName);
		      while (this->_menuGUI->updateScreen())
			this->_menuGUI->draw();
		      this->_menuGUI->getMenu().setIsRanking(false);
		      Sound::stop();
		    }
		  else
		    this->unpause();
		}
	    }
	  this->_menuGUI->getMenu().initParam();
	}
    }
}

void				BomberGame::play(void)
{
  bool				correctQuit = false;

  this->emptyActionPlayer1();
  this->emptyActionPlayer2();
  this->_isPaused = false;
  Sound::stop();
  Sound::playMusic(MUSIC_GAME, -1);
  this->launchPlayers();
  this->_stop = false;
  this->_mapGUI->initialize();
  this->_mapGUI->draw();
  this->_winner = NOBODY;
  while (!this->_stop)
    {
      if (!this->checkPlayers())
	{
	  this->_stop = true;
	  correctQuit = true;
	}
      else
	if (!this->_mapGUI->update())
	  {
	    this->_stop = true;
	    this->_quit = true;
	  }
    }
  if (this->_winner != NOBODY && correctQuit)
    {
      this->loadScore();
      this->changeScore();
      this->saveScore();
    }
  this->setWinnerName();
  this->deleteGame();
  this->_mapGUI->reset();
  Sound::stop();
}

void				BomberGame::deleteGame(void)
{
  for (unsigned int count = 0; count < this->_players.size(); ++count)
    delete(this->_players[count]);
  this->_players.clear();
  delete(this->_map);
  this->_map = NULL;
  this->_actionPlayer1.clear();
  this->_actionPlayer2.clear();
  this->_isPlayer2 = false;
}

bool				BomberGame::checkPlayers(void)
{
  unsigned int			count = 0;
  unsigned int			nbAlives = 0;
  bool				stillPlay = false;
  e_winner			winner = NOBODY;

  while (count < this->_players.size())
    {
      if (this->_players[count]->isAlive())
	{
	  ++nbAlives;
	  if (this->_players[count]->getType() == PLAYER1 ||
	      this->_players[count]->getType() == PLAYER2)
	    {
	      if (this->_players[count]->getType() == PLAYER1)
		winner = PLAYER1_WIN;
	      else if (this->_players[count]->getType() == PLAYER2)
		winner = PLAYER2_WIN;
	      stillPlay = true;
	    }
	}
      ++count;
    }
  if (!(stillPlay && nbAlives > 1))
    {
      if (winner == NOBODY)
	winner = IA_WIN;
      this->_winner = winner;
      return (false);
    }
  return (true);
}

void				BomberGame::affError(const std::string &strError, bool &isOk) const
{
  isOk = false;
  this->_menuGUI->getMenu().createError(strError);
  while (this->_menuGUI->updateScreen())
    this->_menuGUI->draw();
}

bool				BomberGame::isPaused(void) const
{
  return (this->_isPaused);
}

Player				*BomberGame::getPlayer(e_playerType type) const
{
  if (type == PLAYERIA)
    return (NULL);
  for (unsigned int count = 0; count < this->_players.size(); ++count)
    if (this->_players[count]->getType() == type)
      return (dynamic_cast<Player*>(this->_players[count]));
  return (NULL);
}

void				BomberGame::loadScore(void)
{
  LexerScore		lexer;

  try
    {
      lexer.checkFile(".score");
    }
  catch (const std::invalid_argument &err)
    {
      std::cerr << err.what() << std::endl;
      return ;
    }

  ParserScore		parser(lexer.getLines());

  try
    {
      parser.parseFile();
      this->_scoreNames = parser.getNames();
      this->_scoreValues = parser.getScores();
    }
  catch (const std::invalid_argument &err)
    {
      std::cerr << err.what() << std::endl;
    }
}

void				BomberGame::saveScore(void) const
{
  std::vector<std::string> param;
  ParserScore		parser(param);

  parser.writeInFile(".score", this->_scoreNames, this->_scoreValues);
}

void				BomberGame::changeScore(void)
{
  Player			*player1 = this->getPlayer(PLAYER1);
  Player			*player2 = NULL;

  if (this->_isPlayer2)
    player2 = this->getPlayer(PLAYER2);
  if (player1)
    {
      this->_scoreNames.push_back(player1->getName());
      this->_scoreValues.push_back(player1->getScore());
    }
  if (player2)
    {
      this->_scoreNames.push_back(player2->getName());
      this->_scoreValues.push_back(player2->getScore());
    }
  ParserScore::sortScores(this->_scoreValues, this->_scoreNames);
  if (this->_scoreNames.size() > 3)
    this->_scoreNames.resize(3);
  if (this->_scoreValues.size() > 3)
    this->_scoreValues.resize(3);
}

void				BomberGame::setWinnerName()
{
  std::vector<std::string>		nameList;

  nameList.resize(4, "");
  nameList[3] = "nobody";
  nameList[2] = "ia";
  nameList[0] = this->getPlayer(PLAYER1)->getName();
  if (_isPlayer2 == true)
    nameList[1] = this->getPlayer(PLAYER2)->getName();
  this->_winnerName = nameList[static_cast<int>(this->_winner)];
}
