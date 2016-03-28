//
// ParserSave.cpp for ParserSave.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May 14 15:04:37 2014 CHAUCHET Alan
// Last update Thu Jun 12 14:40:55 2014 CHAUCHET Alan
//

#include			"Game/ParserSave.hh"
#include			"Game/BomberGame.hh"
#include			"Game/IA.hh"
#include			"Game/Player.hh"

ParserSave::ParserSave(const std::vector<std::string> &lines, BomberGame *game) : AParser(lines)
{
  this->_game = game;
  this->_words1.push_back("MAP");
  this->_words1.push_back("BOX");
  this->_words1.push_back("PLAYER");
  this->_words2.push_back("PLAYER1");
  this->_words2.push_back("PLAYER2");
  this->_words2.push_back("IA");
  this->_words3.push_back("WALL_D");
  this->_words3.push_back("WALL_I");
  this->_words3.push_back("BONUS_NEW_BOMB");
  this->_words3.push_back("BONUS_ADD_RANGE");
  this->_words3.push_back("BONUS_SPEED_UP");
  this->_correspObj[0] = WALL_D;
  this->_correspObj[1] = WALL_I;
  this->_correspObj[2] = BONUS_NEW_BOMB;
  this->_correspObj[3] = BONUS_ADD_RANGE;
  this->_correspObj[4] = BONUS_SPEED_UP;
  this->_map = NULL;
  this->_mapSizeX = -1;
  this->_mapSizeY = -1;
  this->_functionsCreate[0] = &ParserSave::createMap;
  this->_functionsCreate[1] = &ParserSave::createBox;
  this->_functionsCreate[2] = &ParserSave::createPlayer;
}

bool				ParserSave::checkWordsOrder(const std::string &line)
{
  std::vector<std::string>	words = FunctionString::stringToVector(line);

  if (!words.size())
    return (true);
  for (unsigned int count = 0; count < this->_words1.size(); count++)
    if (this->_words1[count] == words[0])
      {
	if (!((this->*(this->_functionsCreate[count]))(words)))
	  {
	    this->_error = "Save Corrupted!";
	    return (false);
	  }
	return (true);
      }
  this->_error = "Save Corrupted!";
  return (false);
}

void				ParserSave::execData(void)
{
  if (this->_boxs.size() != this->_mapSizeX * this->_mapSizeY || this->_mapSizeX < 2 || this->_mapSizeY < 2)
    throw ParserError("Save Corrupted!");

  std::vector<int>		posX;
  std::vector<int>		posY;

  for (unsigned int count = 0; count < this->_boxs.size(); count++)
    {
      if (this->_boxs[count]->getPosX() < 0 ||
	  static_cast<unsigned int>(this->_boxs[count]->getPosX()) >= this->_mapSizeX
	  || this->_boxs[count]->getPosY() < 0 ||
	  static_cast<unsigned int>(this->_boxs[count]->getPosY()) >= this->_mapSizeY)
	throw ParserError("Save Corrupted!");
      for (unsigned int count2 = 0; count2 < posX.size(); count2++)
	if (posX[count2] == this->_boxs[count]->getPosX() &&
	    posY[count2] == this->_boxs[count]->getPosY())
	  throw ParserError("Save Corrupted!");
      posX.push_back(this->_boxs[count]->getPosX());
      posY.push_back(this->_boxs[count]->getPosY());
    }
  this->_map = new Map(this->_mapSizeX, this->_mapSizeY, this->_boxs);

  int				x;
  int				y;

  for (unsigned int count = 0; count < this->_players.size(); count++)
    {
      x = APlayer::round(this->_players[count]->getPosX());
      y = APlayer::round(this->_players[count]->getPosY());
      if (x < 0 || y < 0 ||
      	  static_cast<unsigned int>(x) >= this->_mapSizeX ||
      	  static_cast<unsigned int>(y) >= this->_mapSizeY
      	  || this->_map->isObstacle(x, y)
	  || this->_players[count]->getNbBombs() < 1
      	  || this->_players[count]->getSpeed() < 0)
	throw ParserError("Save Corrupted!");
    }
}

void				ParserSave::writeInFile(const Map *map, const std::vector<APlayer*> &players, const std::string &fileName) const
{
  std::ofstream			file;

  file.open(fileName.c_str(), std::ofstream::out | std::ofstream::trunc);
  if (file.fail())
    return ;
  file << "MAP " << FunctionString::varToString<unsigned int>(map->getSizeX()) << " " << FunctionString::varToString<unsigned int>(map->getSizeY()) << std::endl;

  std::vector<e_typeObj>	objs;
  std::string			strObjs;

  for (unsigned int count = 0; count < map->getSizeX() * map->getSizeY(); count++)
    {
      objs = map->getObj(count % map->getSizeX(), count / map->getSizeX());
      strObjs = "";
      for (unsigned int count2 = 0; count2 < objs.size(); count2++)
	if (objs[count2] != FIRE && objs[count2] != BOMB)
	  strObjs += (this->_words3[static_cast<int>(objs[count2])] + " ");
      file << "BOX " << count % map->getSizeX()
	   << " " << count / map->getSizeX()
	   << " " << strObjs << std::endl;
    }

  std::string			line;
  IA				*ia;

  for (unsigned int count = 0; count < players.size(); count++)
    {
      line = "PLAYER ";
      line += (this->_words2[static_cast<int>(players[count]->getType())] + " ");
      line += (FunctionString::varToString<double>(players[count]->getPosX()) + " ");
      line += (FunctionString::varToString<double>(players[count]->getPosY()) + " ");
      if (players[count]->getType() == PLAYERIA)
	{
	  if ((ia = dynamic_cast<IA*>(players[count])) == NULL)
	    {
	      file.close();
	      return ;
	    }
	  line += (FunctionString::varToString<int>(ia->getDifficulty()) + " ");
	}
      line += (FunctionString::varToString<double>(players[count]->getSpeed()) + " ");
      line += (FunctionString::varToString<int>(players[count]->getScore()) + " ");
      line += (FunctionString::varToString<unsigned int>(players[count]->getNbBombs()) + " ");
      line += (FunctionString::varToString<unsigned int>(players[count]->getRangeBomb()));
      if (players[count]->getType() == PLAYER1 || players[count]->getType() == PLAYER2)
	line += " " + dynamic_cast<Player*>(players[count])->getName();
      file << line << std::endl;
    }
  file.close();
}

Map				*ParserSave::getMap(void) const
{
  return (this->_map);
}

const std::vector<APlayer*>	&ParserSave::getPlayers(void) const
{
  return (this->_players);
}

bool				ParserSave::createMap(const std::vector<std::string> &words)
{
  if (words.size() != 3 || FunctionString::isNum(words[1]) == false ||
      FunctionString::isNum(words[2]) == false)
    return (false);

  this->_mapSizeX =  FunctionString::stringToVar<unsigned int>(words[1]);
  this->_mapSizeY = FunctionString::stringToVar<unsigned int>(words[2]);
  return (true);
}

bool				ParserSave::createBox(const std::vector<std::string> &words)
{
  if (words.size() < 3 || FunctionString::isNum(words[1]) == false ||
      FunctionString::isNum(words[2]) == false)
    return (false);

  std::vector<e_typeObj>	objs;

  bool				destroy;

  unsigned int x =  FunctionString::stringToVar<unsigned int>(words[1]);
  unsigned int y = FunctionString::stringToVar<unsigned int>(words[2]);

  unsigned int count2;

  for (unsigned int count = 3; count < words.size(); count++)
    {
      count2 = 0;
      while (count2 < this->_words3.size() && this->_words3[count2] != words[count])
	count2++;
      if (count2 == this->_words3.size())
	return (false);
      objs.push_back(this->_correspObj[count2]);
    }
  this->_boxs.push_back(new Box(x, y));
  for (unsigned int count = 0; count < objs.size(); count++)
    this->_boxs[this->_boxs.size() - 1]->addObj(objs[count], destroy);
  return (true);
}

bool				ParserSave::createPlayer(const std::vector<std::string> &words)
{
  if (words.size() < 7)
    return (false);
  if (words[1] == "IA")
    return (this->createIA(words));
  else if (words[1] == "PLAYER1" || words[1] == "PLAYER2")
    return (this->createHumanPlayer(words));
  else
    return (false);
  return (true);
}

bool				ParserSave::createIA(const std::vector<std::string> &words)
{
  if (words.size() != 9)
    return (false);
  for (unsigned int count = 2; count < 9; count++)
    if (!FunctionString::isNum(words[count]))
      return (false);

  APlayer			*ia = new IA(this->_game,
					     FunctionString::stringToVar<double>(words[2]),
					     FunctionString::stringToVar<double>(words[3]),
					     FunctionString::stringToVar<int>(words[4]),
					     this->_game->getPlayersAccess());
  ia->setSpeed(FunctionString::stringToVar<double>(words[5]));
  ia->setScore(FunctionString::stringToVar<unsigned int>(words[6]));

  unsigned int nbBomb = FunctionString::stringToVar<unsigned int>(words[7]);

  while (nbBomb > 1)
    {
      ia->addBomb();
      nbBomb--;
    }
  ia->setRangeBomb(FunctionString::stringToVar<unsigned int>(words[8]));
  this->_players.push_back(ia);
  return (true);
}

bool				ParserSave::createHumanPlayer(const std::vector<std::string> &words)
{
  if (words.size() != 9)
    return (false);

  for (unsigned int count = 2; count < 8; ++count)
    if (!FunctionString::isNum(words[count]))
      return (false);
  for (unsigned int count = 0; count < words[8].size(); ++count)
    if (words[8][count] < 'a' || words[8][count] > 'z')
      return (false);

  for (unsigned int count = 0; count < this->_players.size(); ++count)
    if ((this->_players[count]->getType() == PLAYER1 || this->_players[count]->getType() == PLAYER2)
	&& dynamic_cast<Player*>(this->_players[count])->getName() == words[8])
      return (false);

  APlayer			*player;

  if (words[1] == "PLAYER1")
    {
      for (unsigned int count = 0; count < this->_players.size(); ++count)
	if (this->_players[count]->getType() == PLAYER1)
	  return (false);
      player = new Player(this->_game,
			  PLAYER1,
			  FunctionString::stringToVar<double>(words[2]),
			  FunctionString::stringToVar<double>(words[3]));
    }
  else if (words[1] == "PLAYER2")
    {
      for (unsigned int count = 0; count < this->_players.size(); ++count)
	if (this->_players[count]->getType() == PLAYER2)
	  return (false);
      player = new Player(this->_game,
			  PLAYER2,
			  FunctionString::stringToVar<double>(words[2]),
			  FunctionString::stringToVar<double>(words[3]));
    }

  player->setSpeed(FunctionString::stringToVar<double>(words[4]));
  player->setScore(FunctionString::stringToVar<unsigned int>(words[5]));
  dynamic_cast<Player*>(player)->setName(words[8]);

  unsigned int nbBomb = FunctionString::stringToVar<unsigned int>(words[6]);

  while (nbBomb > 1)
    {
      player->addBomb();
      nbBomb--;
    }
  player->setRangeBomb(FunctionString::stringToVar<unsigned int>(words[7]));
  this->_players.push_back(player);
  return (true);
}

void			ParserSave::clear(void)
{
  if (this->_map != NULL)
    delete(this->_map);
  else
    this->_boxs.clear();
  this->_players.clear();
}
