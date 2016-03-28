//
// Menu.cpp for Menu.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Mon May 26 17:24:45 2014 CHAUCHET Alan
// Last update Thu Jun 12 13:37:19 2014 abgral_f
//

#include		"Menu/Menu.hh"
#include		"Menu/NormalButton.hh"
#include		"Menu/NbListButton.hh"
#include		"Menu/TextListButton.hh"
#include		"Menu/TextBoxButton.hh"
#include                "Game/ListFiles.hh"
#include                "GUI/MenuGUI.hh"
#include		"FunctionString.hpp"
#include		"Game/Key.hh"

Menu::Menu()
{
  this->_geometryMainMenu = new gdl::Geometry();
  this->initParam();
  this->_keyUpPlayer[0] = Key::getKeyPlayer1(KEY_UP);
  this->_keyDownPlayer[0] = Key::getKeyPlayer1(KEY_DOWN);
  this->_keyRightPlayer[0] = Key::getKeyPlayer1(KEY_RIGHT);
  this->_keyLeftPlayer[0] = Key::getKeyPlayer1(KEY_LEFT);
  this->_keyBombPlayer[0] = Key::getKeyPlayer1(KEY_BOMB);
  this->_keyUpPlayer[1] = Key::getKeyPlayer2(KEY_UP);
  this->_keyDownPlayer[1] = Key::getKeyPlayer2(KEY_DOWN);
  this->_keyRightPlayer[1] = Key::getKeyPlayer2(KEY_RIGHT);
  this->_keyLeftPlayer[1] = Key::getKeyPlayer2(KEY_LEFT);
  this->_keyBombPlayer[1] = Key::getKeyPlayer2(KEY_BOMB);
}

Menu::~Menu()
{
  while (!this->_buttonList.empty())
    this->_buttonList.pop_back();
  while (!this->_textList.empty())
    this->_textList.pop_back();
  if (_geometryMainMenu)
    delete this->_geometryMainMenu;
}

void			Menu::initParam()
{
  this->_save = false;
  this->_moveCursor = 1;
  this->_quit = false;
  this->_play = false;
  this->_mapChoosen = "";
  this->_mapLenght = 5;
  this->_mapWidth = 5;
  this->_twoPlayers = false;
  this->_nbIaPlayers = 0;
  this->_iaDifficulty = 0;
  this->_loadGame = "";
  this->_namePlayer[0] = "";
  this->_namePlayer[1] = "";
  this->_effectsSound = 50;
  this->_musicSound = 50;
  this->_pause = false;
  this->_isBackup = false;
  this->_isHowToPlay = false;
  this->_isRanking = false;
}

void			Menu::setIsRanking(bool value)
{
  this->_isRanking = value;
}

bool			Menu::getIsRanking() const
{
  return (this->_isRanking);
}

bool                    Menu::getIsBackup() const
{
  return (this->_isBackup);
}

void                    Menu::setIsBackup(bool value)
{
  this->_isBackup = value;
}

void                    Menu::setBackup()
{
  this->_backup = static_cast<TextBoxButton *>(this->_buttonList[0])->getName();
  this->_isBackup = true;
}

const std::string       &Menu::getBackup() const
{
  return (this->_backup);
}

void		       Menu::setQuit(bool value)
{
  this->_quit = value;
}

bool			Menu::getQuit() const
{
  return (this->_quit);
}

bool			Menu::getSave() const
{
  return (this->_save);
}

void			Menu::setSave(bool value)
{
  this->_save = value;
}

bool			Menu::getPause() const
{
  return (this->_pause);
}

void			Menu::setPause(bool value)
{
  this->_pause = value;
}

void			Menu::unpause()
{
  this->_pause = false;
}

const std::string      &Menu::getMapChoosen() const
{
  return (this->_mapChoosen);
}

void                          Menu::setMapChoosen()
{
  this->_mapChoosen = static_cast<TextListButton *>(this->_buttonList[0])->getList()
    [static_cast<unsigned int>(static_cast<TextListButton *>(this->_buttonList[0])->getCursorList())];
}

void		      Menu::quitGame()
{
  this->_quit = true;
}

bool		      Menu::getPlay() const
{
  return (this->_play);
}

void		      Menu::playGame()
{
  if (((_twoPlayers == true
       && _namePlayer[0] != "" && _namePlayer[1] != ""
       && _namePlayer[0] != _namePlayer[1])
       || (_twoPlayers == false && _namePlayer[0] != "")) || _save == true)
    {
      this->_play = true;
      this->createLoading();
      _save = false;
    }
  else if (_namePlayer[0] == "" || _namePlayer[1] == "")
    {
      this->_textList.push_back(new Text(-25, 20, 5, 5, "enter a name", true));
      this->_textList.back()->buildText();
    }
}

int		      Menu::getCursor() const
{
  return (this->_cursor);
}

int                   Menu::getMapLenght() const
{
  return (this->_mapLenght);
}

void                  Menu::setMapLenght()
{
  this->_mapLenght = static_cast<NbListButton *>(this->_buttonList[0])->getCurrentValue();
}

int                   Menu::getMapWidth() const
{
  return (this->_mapWidth);
}

void                  Menu::setMapWidth()
{
  this->_mapWidth = static_cast<NbListButton *>(this->_buttonList[1])->getCurrentValue();
}

bool                  Menu::getTwoPlayers() const
{
  return (this->_twoPlayers);
}

void                  Menu::setTwoPlayers()
{
  if (static_cast<TextListButton *>(this->_buttonList[0])->getList()
      [static_cast<unsigned int>(static_cast<TextListButton *>(this->_buttonList[0])->getCursorList())] == "yes")
    this->_twoPlayers = true;
  else
    this->_twoPlayers = false;
}

int                   Menu::getNbIaPlayers() const
{
  return (this->_nbIaPlayers);
}

void                  Menu::setNbIaPlayers()
{
  this->_nbIaPlayers = static_cast<NbListButton *>(this->_buttonList[1])->getCurrentValue();
}

int                   Menu::getIaDifficulty() const
{
  return (this->_iaDifficulty);
}

void                  Menu::setLoadGame()
{
  this->_loadGame = static_cast<TextListButton *>(this->_buttonList[0])->getList()
    [static_cast<unsigned int>(static_cast<TextListButton *>(this->_buttonList[0])->getCursorList())];
}

const std::string     &Menu::getLoadGame() const
{
  return (this->_loadGame);
}

void                  Menu::setIaDifficulty()
{
  if (static_cast<TextListButton *>(this->_buttonList[2])->getList()
      [static_cast<unsigned int>(static_cast<TextListButton *>(this->_buttonList[2])->getCursorList())] == "easy")
    this->_iaDifficulty = 0;
  if (static_cast<TextListButton *>(this->_buttonList[2])->getList()
      [static_cast<unsigned int>(static_cast<TextListButton *>(this->_buttonList[2])->getCursorList())] == "normal")
    this->_iaDifficulty = 1;
  if (static_cast<TextListButton *>(this->_buttonList[2])->getList()
      [static_cast<unsigned int>(static_cast<TextListButton *>(this->_buttonList[2])->getCursorList())] == "hard")
    this->_iaDifficulty = 2;
}

int		         Menu::getEffectsSound() const
{
  return (this->_effectsSound);
}

void	                 Menu::setEffectsSound()
{
  this->_effectsSound = static_cast<NbListButton *>(this->_buttonList[1])->getCurrentValue();
}

int		         Menu::getMusicSound() const
{
  return (this->_musicSound);
}

void                  Menu::setMusicSound()
{
  this->_musicSound = static_cast<NbListButton *>(this->_buttonList[0])->getCurrentValue();
}

const std::string         &Menu::getNamePlayer1() const
{
  return (this->_namePlayer[0]);
}

void                  Menu::setNamePlayer1()
{
  this->_namePlayer[0] = static_cast<TextBoxButton *>(this->_buttonList[0])->getName();
}

const std::string         &Menu::getNamePlayer2() const
{
  return (this->_namePlayer[1]);
}

void                  Menu::setNamePlayer2()
{
  this->_namePlayer[1] = static_cast<TextBoxButton *>(this->_buttonList[1])->getName();
}

int                   Menu::getKeyUpPlayer1() const
{
  return (this->_keyUpPlayer[0]);
}

void                  Menu::setKeyUpPlayer1()
{
  this->_keyUpPlayer[0] = getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[0])->getName());
  Key::setKeyPlayer1(KEY_UP, getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[0])->getName()));
}

int                   Menu::getKeyDownPlayer1() const
{
  return (this->_keyDownPlayer[0]);
}

void                  Menu::setKeyDownPlayer1()
{
  this->_keyDownPlayer[0] = getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[2])->getName());
  Key::setKeyPlayer1(KEY_DOWN, getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[2])->getName()));
}

int                   Menu::getKeyRightPlayer1() const
{
  return (this->_keyRightPlayer[0]);
}

void                  Menu::setKeyRightPlayer1()
{
  this->_keyRightPlayer[0] = getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[6])->getName());
  Key::setKeyPlayer1(KEY_RIGHT, getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[6])->getName()));
}

int                   Menu::getKeyLeftPlayer1() const
{
  return (this->_keyLeftPlayer[0]);
}

void                  Menu::setKeyLeftPlayer1()
{
  this->_keyLeftPlayer[0] = getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[4])->getName());
  Key::setKeyPlayer1(KEY_LEFT, getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[4])->getName()));
}

int                   Menu::getKeyBombPlayer1() const
{
  return (this->_keyBombPlayer[0]);
}

void                  Menu::setKeyBombPlayer1()
{
  this->_keyBombPlayer[0] = getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[8])->getName());
  Key::setKeyPlayer1(KEY_BOMB, getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[8])->getName()));
}

int                   Menu::getKeyUpPlayer2() const
{
  return (this->_keyUpPlayer[1]);
}

void                  Menu::setKeyUpPlayer2()
{
  this->_keyUpPlayer[1] = getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[1])->getName());
  Key::setKeyPlayer2(KEY_UP, getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[1])->getName()));
}

int                   Menu::getKeyDownPlayer2() const
{
  return (this->_keyDownPlayer[1]);
}

void                  Menu::setKeyDownPlayer2()
{
  this->_keyDownPlayer[1] = getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[3])->getName());
  Key::setKeyPlayer2(KEY_DOWN, getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[3])->getName()));
}

int                   Menu::getKeyRightPlayer2() const
{
  return (this->_keyRightPlayer[1]);
}

void                  Menu::setKeyRightPlayer2()
{
  this->_keyRightPlayer[1] = getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[7])->getName());
  Key::setKeyPlayer2(KEY_RIGHT, getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[7])->getName()));
}

int                   Menu::getKeyLeftPlayer2() const
{
  return (this->_keyLeftPlayer[1]);
}

void                  Menu::setKeyLeftPlayer2()
{
  this->_keyLeftPlayer[1] = getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[5])->getName());
  Key::setKeyPlayer2(KEY_LEFT, getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[5])->getName()));
}

int                   Menu::getKeyBombPlayer2() const
{
  return (this->_keyBombPlayer[1]);
}

void                  Menu::setKeyBombPlayer2()
{
  this->_keyBombPlayer[1] = getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[9])->getName());
  Key::setKeyPlayer2(KEY_BOMB, getKeyNbEquivalent(static_cast<TextBoxButton *>(this->_buttonList[9])->getName()));
}

void		      Menu::saveParam()
{
  this->_moveCursor = 1;
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    {
      if (this->_buttonList[i]->getType() != AButton::Normal)
	this->_buttonList[i]->setIsSelect(true);
      else
	this->_buttonList[i]->setIsSelect(false);
    }
  this->doAction();
  (this->*(this->_toCall))();
}

void                  Menu::createButton(float posX, float posY,
					 float sizeX, float sizeY,
					 fctPtr method, int min, int max, int isMusic, int value)
{
  this->_buttonList.push_back(new NbListButton(posX, posY, sizeX, sizeY, method, min, max, this, value, isMusic));
}

void                  Menu::createButton(float posX, float posY,
					 float sizeX, float sizeY,
					 fctPtr method, std::string name)
{
  this->_buttonList.push_back(new NormalButton(posX, posY, sizeX, sizeY, method, name, this));
}

void                  Menu::createButton(float posX, float posY,
					 float sizeX, float sizeY,
					 fctPtr method, const std::string &_default, bool oneCharac)
{
  this->_buttonList.push_back(new TextBoxButton(posX, posY, sizeX, sizeY, method, _default, oneCharac, this));
}

void                  Menu::createButton(float posX, float posY,
					 float sizeX, float sizeY,
					 fctPtr method, const std::vector<std::string> &list)
{
  this->_buttonList.push_back(new TextListButton(posX, posY, sizeX, sizeY, method, list, this));
}

void			Menu::createHowToPlay()
{
  this->buildMenu();
  this->_isHowToPlay = true;
  this->delList();
  this->_cursor = 0;
  this->createButton(-44, -26, 47, 8, &Menu::createMenu, "back");
  this->_buttonList[this->_cursor]->setIsSelect(true);
    for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void                  Menu::createSave()
{
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->_textList.push_back(new Text(-25, 10, 5, 5, "backup name"));
  this->createButton(-25, -2, 50, 8, &Menu::setBackup, "", false);
  this->createButton(5, -26, 40, 8, &Menu::saveParam, "save");
  this->_buttonList[this->_cursor]->setIsSelect(true);
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void		      Menu::createResults(const std::vector<std::string> &names,
					  std::vector<unsigned int> scores, const std::string &winner)
{
  int			  y = 0;
  std::string		  text;


  this->_isRanking = true;
  text = winner;
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->_buttonList[this->_cursor]->setIsSelect(true);
  this->_textList.push_back(new Text(-5, 23, 5, 5, text));
  this->_textList[0]->setIsCentered(true);
  for (unsigned int i = 0 ; i != names.size() ; i++)
    {
      std::string             result;

      this->_textList.push_back(new Text(-15,  y, 5, 5, names[i]));
      result = FunctionString::varToString<unsigned int>(scores[i]);
      this->_textList.push_back(new Text(24, y, 5, 5, result));
      y -= 9;
    }
  this->_textList.push_back(new Text(-5, -27, 5, 5, "press space"));
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    {
      this->_textList[i]->setIsCentered(true);
      this->_textList[i]->buildText();
    }
}

void		      Menu::createName()
{
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  if (_twoPlayers == false)
    {
      this->_textList.push_back(new Text(-25, 10, 5, 5, "player 1"));
      this->createButton(-25, -2, 50, 8, &Menu::setNamePlayer1, _namePlayer[0], false);
    }
  else
    {
      this->_textList.push_back(new Text(-25, 13, 5, 5, "player 1"));
      this->createButton(-25, 6, 50, 8, &Menu::setNamePlayer1, _namePlayer[0], false);
      this->_textList.push_back(new Text(-25, -4, 5, 5, "player 2"));
      this->createButton(-25, -12, 50, 8, &Menu::setNamePlayer2, _namePlayer[1], false);
    }
  this->createButton(-44, -26, 47, 8, &Menu::createPlayerList, "back");
  this->createButton(5, -26, 40, 8, &Menu::saveParam, "play");
  this->_toCall = &Menu::playGame;
  this->_buttonList[this->_cursor]->setIsSelect(true);
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void                  Menu::createPause()
{
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->createButton(-27, 12, 55, 8, &Menu::createSave, "save");
  this->createButton(-27, 2, 55, 8, &Menu::createOptionsMenu, "options");
  this->createButton(-27, -9, 55, 8, &Menu::unpause, "back to game");
  this->createButton(-27, -19, 55, 8, &Menu::quitGame, "quit game");
  this->_buttonList[this->_cursor]->setIsSelect(true);
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}


void                  Menu::createMenu()
{
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->createButton(-44, 18, 50, 8, &Menu::createSelectionMap, "new game");
  this->createButton(-44, 8, 50, 8, &Menu::createLoadGame, "load game");
  this->createButton(-44, -2, 50, 8, &Menu::createOptionsMenu, "options");
  this->createButton(-44, -12, 50, 8, &Menu::createHowToPlay, "how to play");
  this->createButton(-44, -22, 50, 8, &Menu::quitGame, "quit");
  this->_buttonList[this->_cursor]->setIsSelect(true);
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void		      Menu::createRandomMap()
{
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->_textList.push_back(new Text(-18, 22, 5, 5, "map lenght"));
  this->createButton(-25, 14, 50, 8, &Menu::setMapLenght, _mapLenght, 100, 0, _mapLenght);
  this->_textList.push_back(new Text(-16, 4, 5, 5, "map width"));
  this->createButton(-25, -3, 50, 8, &Menu::setMapWidth, _mapWidth, 100, 0, _mapWidth);
  this->createButton(-44, -26, 47, 8, &Menu::createSelectionMap, "back");
  this->createButton(5, -26, 40, 8, &Menu::saveParam, "next");
  this->_buttonList[this->_cursor]->setIsSelect(true);
  this->_toCall = &Menu::createPlayerList;
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void		      Menu::createPlayerList()
{
  std::vector<std::string> list;
  list.push_back("easy");
  list.push_back("normal");
  list.push_back("hard");
  std::vector<std::string> listTwo;
  listTwo.push_back("no");
  listTwo.push_back("yes");
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->_textList.push_back(new Text(-20, 23, 5, 5, "two players"));
  this->createButton(-25, 17, 50, 8, &Menu::setTwoPlayers, listTwo);
  this->_textList.push_back(new Text(-20, 8, 5, 5, "ia players"));
  this->createButton(-25, 1, 50, 8, &Menu::setNbIaPlayers, _nbIaPlayers, (_mapLenght * _mapWidth - 2) / 2, 0);
  this->_textList.push_back(new Text(-27, -8, 5, 5, "ia difficulty"));
  this->createButton(-25, -15, 50, 8, &Menu::setIaDifficulty, list);
  this->createButton(-44, -26, 40, 8, &Menu::createSelectionMap, "back");
  this->createButton(5, -26, 40, 8, &Menu::saveParam, "next");
  this->_toCall = &Menu::createName;
  this->_buttonList[this->_cursor]->setIsSelect(true);
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void		      Menu::createMapList()
{
  std::vector<std::string> list;
  ListFiles::openDir("./.Map", list);
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->_textList.push_back(new Text(-27, 20, 5, 5, "map selection"));
  this->createButton(-25, 12, 50, 8, &Menu::setMapChoosen, list);
  this->createButton(-44, -26, 47, 8, &Menu::createSelectionMap, "back");
  this->_buttonList[this->_cursor]->setIsSelect(true);
  if (list.size() != 0)
    {
      this->createButton(5, -26, 40, 8, &Menu::saveParam, "next");
      this->_toCall = &Menu::createPlayerList;
    }
  this->_buttonList[this->_cursor]->setIsSelect(true);
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void		      Menu::createSelectionMap()
{
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->createButton(-44, 20, 47, 8, &Menu::createMapList, "map list");
  this->createButton(-44, 10, 47, 8, &Menu::createRandomMap, "random map");
  this->createButton(-44, -26, 47, 8, &Menu::createMenu, "back");
  this->_buttonList[this->_cursor]->setIsSelect(true);
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
}

void		      Menu::createControls()
{
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->_textList.push_back(new Text(-3, 23, 3.5, 3.5, "player 1"));
  this->_textList.push_back(new Text(24, 23, 3.5, 3.5, "player 2"));
  this->_textList.push_back(new Text(-46, 19, 5, 5, "move up"));
  this->createButton(-4, 18, 25, 5, &Menu::setKeyUpPlayer1, getKeyStrEquivalent(_keyUpPlayer[0]), true);
  this->createButton(23, 18, 25, 5, &Menu::setKeyUpPlayer2, getKeyStrEquivalent(_keyUpPlayer[1]), true);
  this->_textList.push_back(new Text(-46, 10, 5, 5, "move down"));
  this->createButton(-4, 10, 25, 5, &Menu::setKeyDownPlayer1, getKeyStrEquivalent(_keyDownPlayer[0]), true);
  this->createButton(23, 10, 25, 5, &Menu::setKeyDownPlayer2, getKeyStrEquivalent(_keyDownPlayer[1]), true);
  this->_textList.push_back(new Text(-46, 1, 5, 5, "move left"));
  this->createButton(-4, 1, 25, 5, &Menu::setKeyLeftPlayer1, getKeyStrEquivalent(_keyLeftPlayer[0]), true);
  this->createButton(23, 1, 25, 5, &Menu::setKeyLeftPlayer2, getKeyStrEquivalent(_keyLeftPlayer[1]), true);
  this->_textList.push_back(new Text(-46, -8, 5, 5, "move right"));
  this->createButton(-4, -8, 25, 5, &Menu::setKeyRightPlayer1, getKeyStrEquivalent(_keyRightPlayer[0]), true);
  this->createButton(23, -8, 25, 5, &Menu::setKeyRightPlayer2, getKeyStrEquivalent(_keyRightPlayer[1]), true);
  this->_textList.push_back(new Text(-46, -17, 5, 5, "drop bomb"));
  this->createButton(-4, -17, 25, 5, &Menu::setKeyBombPlayer1, getKeyStrEquivalent(_keyBombPlayer[0]), true);
  this->createButton(23, -17, 25, 5, &Menu::setKeyBombPlayer2, getKeyStrEquivalent(_keyBombPlayer[1]), true);
  this->createButton(-44, -26, 40, 8, &Menu::saveParam, "back");
  this->_toCall = &Menu::createOptionsMenu;
  this->_buttonList[this->_cursor]->setIsSelect(true);
  this->_moveCursor = 2;
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void		      Menu::createMusic()
{
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->_textList.push_back(new Text(-20, 22, 5, 5, "sound volume"));
  this->createButton(-25, 14, 50, 8, &Menu::setMusicSound, 0, 100, 1, this->_musicSound);
  this->_textList.push_back(new Text(-25, 4, 5, 5, "effects sound"));
  this->createButton(-25, -3, 50, 8, &Menu::setEffectsSound, 0, 100, 2, this->_effectsSound);
  this->createButton(-44, -26, 40, 8, &Menu::saveParam, "back");
  this->_toCall = &Menu::createOptionsMenu;
  this->_buttonList[this->_cursor]->setIsSelect(true);
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void                  Menu::createOptionsMenu()
{
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->createButton(-44, 20, 47, 8, &Menu::createControls, "controls");
  this->createButton(-44, 10, 47, 8, &Menu::createMusic, "sound");
  if (this->_pause == true)
    this->createButton(-44, -26, 40, 8, &Menu::createPause, "back");
  else
    this->createButton(-44, -26, 40, 8, &Menu::createMenu, "back");
  this->_buttonList[this->_cursor]->setIsSelect(true);
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
}
void			Menu::createLoadGame()
{
  std::vector<std::string> list;
  ListFiles::openDir("./.Save", list);
  this->buildMenu();
  this->delList();
  this->_cursor = 0;
  this->_textList.push_back(new Text(-29, 20, 5, 5, "game selection"));
  this->createButton(-25, 12, 50, 8, &Menu::setLoadGame, list);
  this->createButton(-44, -26, 47, 8, &Menu::createMenu, "back");
  if (list.size() != 0)
    {
      this->createButton(5, -26, 40, 8, &Menu::saveParam, "play");
      this->_toCall = &Menu::playGame;
    }
  this->_save = true;
  this->_buttonList[this->_cursor]->setIsSelect(true);
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    this->_buttonList[i]->buildNewGeo();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void			Menu::createLoading()
{
  this->delList();
  this->_geometryMainMenu = NULL;
  this->_textList.push_back(new Text(-28, 8, 10, 10, "loading"));
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void			Menu::createError(const std::string &error)
{
  this->delList();
  this->_geometryMainMenu = NULL;
  this->_textList.push_back(new Text(-29, 5, 5, 5, error, true));
  this->_textList.push_back(new Text(-23, -27, 5, 5, "press space", true));
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->buildText();
}

void                  Menu::delList()
{
  while (!this->_buttonList.empty())
    this->_buttonList.pop_back();
  while (!this->_textList.empty())
    this->_textList.pop_back();
  if (!this->_geometryMainMenu)
    delete this->_geometryMainMenu;
}

const std::vector<AButton *> &Menu::getButtonList() const
{
  return (this->_buttonList);
}

void		      Menu::moveCursor(int value)
{
  if (this->_buttonList.size() != 0)
    {
      this->_buttonList[this->_cursor]->setIsSelect(false);
      this->_buttonList[this->_cursor]->buildNewGeo();
      if (this->_cursor + value < 0)
	this->_cursor = this->_buttonList.size() - 1;
      else if (static_cast<unsigned int>(this->_cursor + value) >= this->_buttonList.size())
	this->_cursor = 0;
      else
	this->_cursor += value;
      this->_buttonList[this->_cursor]->setIsSelect(true);
      this->_buttonList[this->_cursor]->buildNewGeo();
    }
}

gdl::Texture           &Menu::getTextureButton()
{
  return (this->_textureButton);
}

gdl::Texture           &Menu::getTextureLetters()
{
  return (this->_textureLetters);
}

gdl::Texture           &Menu::getTextureArrow()
{
  return (this->_textureArrow);
}

void			Menu::loadTextures()
{
  if (_textureLetters.load("./texture/Alphabet.tga") == false
      || _textureButton.load("./texture/Button.tga") == false
      || _textureArrow.load("./texture/Arrow.tga") == false
      || _textureMainMenu.load("./texture/Menu.tga") == false
      || _textureRanking.load("./texture/Ranking.tga") == false
      || _textureHowToPlay.load("./texture/HowToPlay.tga") == false)
    throw std::runtime_error("Error one Texture::load");
}

void                   Menu::doAction()
{
  unsigned int		i = 0;

  while  (i != this->_buttonList.size())
    {
      if (this->_buttonList[i]->getIsSelect() == true
	  && this->_buttonList[i]->getType() == AButton::Normal)
	{
	  (this->*(this->_buttonList[i]->getMethod()))();
	  return;
	}
      else if (this->_buttonList[i]->getIsSelect() == true)
	(this->*(this->_buttonList[i]->getMethod()))();
      i++;
    }
}

void			Menu::buildMenu()
{
  this->_isHowToPlay = false;
  if (!this->_geometryMainMenu)
    delete this->_geometryMainMenu;
  this->_geometryMainMenu = new gdl::Geometry();
  _geometryMainMenu->pushVertex(glm::vec3(-49, 38, 0));
  _geometryMainMenu->pushVertex(glm::vec3(49, 38, 0));
  _geometryMainMenu->pushVertex(glm::vec3(49, -38, 0));
  _geometryMainMenu->pushVertex(glm::vec3(-49, -38, 0));

  _geometryMainMenu->pushUv(glm::vec2(0.0, 1));
  _geometryMainMenu->pushUv(glm::vec2(1, 1));
  _geometryMainMenu->pushUv(glm::vec2(1, 0.0));
  _geometryMainMenu->pushUv(glm::vec2(0.0, 0.0));

  _geometryMainMenu->build();
}

void			Menu::drawMenu(gdl::BasicShader _shader, glm::mat4 transform, int flag)
{
  if (_isHowToPlay == true)
    this->_textureHowToPlay.bind();
  else if (_isRanking == true)
    this->_textureRanking.bind();
  else
    this->_textureMainMenu.bind();
 if (this->_geometryMainMenu != NULL)
    this->_geometryMainMenu->draw(_shader, transform, flag);
  this->_textureLetters.bind();
  for (unsigned int i = 0 ; i != this->_textList.size() ; i++)
    this->_textList[i]->getGeometryText()->draw(_shader, transform, flag);
  for (unsigned int i = 0 ; i != this->_buttonList.size() ; i++)
    {
      this->_textureButton.bind();
      this->_buttonList[i]->getGeometryButton()->draw(_shader, transform, flag);
      this->_textureLetters.bind();
      this->_buttonList[i]->getGeometryLetters()->draw(_shader, transform, GL_QUADS);
      if (this->_buttonList[i]->getType() == AButton::Arrow || this->_buttonList[i]->getType() == AButton::ArrowNb)
	{
	  this->_textureArrow.bind();
	  if (static_cast<AListButton *>(this->_buttonList[i])->getDisplayRight() == true)
	    static_cast<AListButton *>(this->_buttonList[i])->getGeometryRightArrow()->draw(_shader, transform, flag);
	  if (static_cast<AListButton *>(this->_buttonList[i])->getDisplayLeft() == true)
	    static_cast<AListButton *>(this->_buttonList[i])->getGeometryLeftArrow()->draw(_shader, transform, flag);
	}
    }
}

void                  Menu::initKeyList()
{
  _keyCodeList.push_back(SDLK_SPACE);
  _keyCodeList.push_back(SDLK_0);
  _keyCodeList.push_back(SDLK_1);
  _keyCodeList.push_back(SDLK_2);
  _keyCodeList.push_back(SDLK_3);
  _keyCodeList.push_back(SDLK_4);
  _keyCodeList.push_back(SDLK_5);
  _keyCodeList.push_back(SDLK_6);
  _keyCodeList.push_back(SDLK_7);
  _keyCodeList.push_back(SDLK_8);
  _keyCodeList.push_back(SDLK_9);
  _keyCodeList.push_back(SDLK_a);
  _keyCodeList.push_back(SDLK_b);
  _keyCodeList.push_back(SDLK_c);
  _keyCodeList.push_back(SDLK_d);
  _keyCodeList.push_back(SDLK_e);
  _keyCodeList.push_back(SDLK_f);
  _keyCodeList.push_back(SDLK_g);
  _keyCodeList.push_back(SDLK_h);
  _keyCodeList.push_back(SDLK_i);
  _keyCodeList.push_back(SDLK_j);
  _keyCodeList.push_back(SDLK_k);
  _keyCodeList.push_back(SDLK_l);
  _keyCodeList.push_back(SDLK_m);
  _keyCodeList.push_back(SDLK_n);
  _keyCodeList.push_back(SDLK_o);
  _keyCodeList.push_back(SDLK_p);
  _keyCodeList.push_back(SDLK_q);
  _keyCodeList.push_back(SDLK_r);
  _keyCodeList.push_back(SDLK_s);
  _keyCodeList.push_back(SDLK_t);
  _keyCodeList.push_back(SDLK_u);
  _keyCodeList.push_back(SDLK_v);
  _keyCodeList.push_back(SDLK_w);
  _keyCodeList.push_back(SDLK_x);
  _keyCodeList.push_back(SDLK_y);
  _keyCodeList.push_back(SDLK_z);
  _keyCodeList.push_back(SDLK_UP);
  _keyCodeList.push_back(SDLK_DOWN);
  _keyCodeList.push_back(SDLK_LEFT);
  _keyCodeList.push_back(SDLK_RIGHT);
  _keyStrList.push_back(new std::string("space bar"));
  _keyStrList.push_back(new std::string("0"));
  _keyStrList.push_back(new std::string("1"));
  _keyStrList.push_back(new std::string("2"));
  _keyStrList.push_back(new std::string("3"));
  _keyStrList.push_back(new std::string("4"));
  _keyStrList.push_back(new std::string("5"));
  _keyStrList.push_back(new std::string("6"));
  _keyStrList.push_back(new std::string("7"));
  _keyStrList.push_back(new std::string("8"));
  _keyStrList.push_back(new std::string("9"));
  _keyStrList.push_back(new std::string("a"));
  _keyStrList.push_back(new std::string("b"));
  _keyStrList.push_back(new std::string("c"));
  _keyStrList.push_back(new std::string("d"));
  _keyStrList.push_back(new std::string("e"));
  _keyStrList.push_back(new std::string("f"));
  _keyStrList.push_back(new std::string("g"));
  _keyStrList.push_back(new std::string("h"));
  _keyStrList.push_back(new std::string("i"));
  _keyStrList.push_back(new std::string("j"));
  _keyStrList.push_back(new std::string("k"));
  _keyStrList.push_back(new std::string("l"));
  _keyStrList.push_back(new std::string("m"));
  _keyStrList.push_back(new std::string("n"));
  _keyStrList.push_back(new std::string("o"));
  _keyStrList.push_back(new std::string("p"));
  _keyStrList.push_back(new std::string("q"));
  _keyStrList.push_back(new std::string("r"));
  _keyStrList.push_back(new std::string("s"));
  _keyStrList.push_back(new std::string("t"));
  _keyStrList.push_back(new std::string("u"));
  _keyStrList.push_back(new std::string("v"));
  _keyStrList.push_back(new std::string("w"));
  _keyStrList.push_back(new std::string("x"));
  _keyStrList.push_back(new std::string("y"));
  _keyStrList.push_back(new std::string("z"));
  _keyStrList.push_back(new std::string("up"));
  _keyStrList.push_back(new std::string("down"));
  _keyStrList.push_back(new std::string("left"));
  _keyStrList.push_back(new std::string("right"));
 }

 const std::vector<int> &Menu::getKeyCodeList() const
 {
   return (this->_keyCodeList);
 }

 const std::vector<std::string *> &Menu::getKeyStrList() const
 {
   return (this->_keyStrList);
 }

 int                   Menu::getKeyNbEquivalent(const std::string &key)
 {
   unsigned int i = 0;
   while (i != this->_keyStrList.size() && *(this->_keyStrList[i]) != key)
     i++;
  return (_keyCodeList[i]);
}

const std::string    &Menu::getKeyStrEquivalent(int key)
{
  unsigned int i = 0;
  while (i != this->_keyCodeList.size() && this->_keyCodeList[i] != key)
    i++;
  return (*_keyStrList[i]);
}

int			Menu::getMoveCursor() const
{
  return (this->_moveCursor);
}

bool			Menu::isKeyAlreadyUsed(const std::string &key) const
{
  for (unsigned int i = 0 ; i != _buttonList.size() ; i++)
    {
      if (_buttonList[i]->getType() == AButton::TextBox
	  && static_cast<TextBoxButton *>(_buttonList[i])->getName() == key)
	return true;
    }
  return false;
}
