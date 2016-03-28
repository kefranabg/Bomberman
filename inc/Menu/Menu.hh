//
// Menu.hh for Menu.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Sat May 10 15:12:54 2014 abgral_f
// Last update Thu Jun 12 12:57:29 2014 abgral_f
//

#ifndef			MENU_HH_
# define		MENU_HH_

#include		<iostream>
#include		<string>
#include		<vector>
#include		<stdexcept>
#include		<Texture.hh>
#include		<BasicShader.hh>
#include                <Geometry.hh>
#include                <glm/glm.hpp>
#include		"Text.hh"
#include		"AButton.hh"

class			Button;

class			Menu
{
public:
  typedef void			(Menu::*fctPtr)(void);

public:
  Menu();
  ~Menu();
  void				createButton(float, float, float, float, fctPtr, int, int, int isMusic, int value = 0);
  void				createButton(float, float, float, float, fctPtr, std::string);
  void				createButton(float, float, float, float, fctPtr, const std::string &, bool);
  void				createButton(float, float, float, float, fctPtr, const std::vector<std::string> &);
  void				drawMenu(gdl::BasicShader, glm::mat4, int);
  int				getCursor() const;
  void				createPause();
  void				createResults(const std::vector<std::string> &, std::vector<unsigned int>, const std::string &);
  void				createMenu();
  void				createOptionsMenu();
  void				createSelectionMap();
  void				createRandomMap();
  void				createMapList();
  void				createPlayerList();
  void				createLoadGame();
  void				createName();
  void				createLoading();
  void				createError(const std::string &);
  void				createMusic();
  void				createControls();
  void				createSave();
  void				createHowToPlay();
  void				delList();
  const std::vector<AButton *>	&getButtonList() const;
  void				moveCursor(int);
  gdl::Texture			&getTextureButton();
  gdl::Texture                  &getTextureLetters();
  gdl::Texture			&getTextureArrow();
  void				loadTextures();
  void				doAction();
  void				buildMenu();
  void				saveParam();
  void                          initKeyList();
  const std::vector<int>	&getKeyCodeList() const;
  const std::vector<std::string *> &getKeyStrList() const;
  int				getKeyNbEquivalent(const std::string &);
  const std::string	        &getKeyStrEquivalent(int);
  int				getMoveCursor() const;
  bool				isKeyAlreadyUsed(const std::string &) const;
  void				initParam();
  void				unpause();
  bool                          getIsBackup() const;
  void                          setIsBackup(bool);
  bool				getIsRanking() const;
  void				setIsRanking(bool);
private:
  bool				_pause;
  std::vector<int>              _keyCodeList;
  std::vector<std::string *>    _keyStrList;
  fctPtr			_toCall;
  std::vector<AButton *>	_buttonList;
  std::vector<Text *>		_textList;
  bool				_error;
  int				_cursor;
  int				_moveCursor;
  gdl::Texture			_textureMainMenu;
  gdl::Texture			_textureButton;
  gdl::Texture			_textureLetters;
  gdl::Texture			_textureArrow;
  gdl::Texture			_textureHowToPlay;
  gdl::Texture			_textureRanking;
  gdl::Geometry			*_geometryMainMenu;
  bool				_isBackup;
  bool				_isHowToPlay;
  bool				_isRanking;
public:
  void				setQuit(bool);
  bool				getQuit() const;
  bool				getSave() const;
  void				setSave(bool);
  bool				getPause() const;
  void				setPause(bool);
  void				quitGame();
  bool                          getPlay() const;
  void				playGame();
  const std::string		&getMapChoosen() const;
  void				setMapChoosen();
  int				getMapLenght() const;
  void				setMapLenght();
  int				getMapWidth() const;
  void				setMapWidth();
  bool				getTwoPlayers() const;
  void				setTwoPlayers();
  int				getNbIaPlayers() const;
  void				setNbIaPlayers();
  int				getIaDifficulty() const;
  void				setIaDifficulty();
  int				getEffectsSound() const;
  void				setEffectsSound();
  int				getMusicSound() const;
  void				setMusicSound();
  const std::string		&getLoadGame() const;
  void				setLoadGame();
  const std::string		&getNamePlayer1() const;
  void				setNamePlayer1();
  const std::string		&getNamePlayer2() const;
  void				setNamePlayer2();
  int				getKeyUpPlayer1() const;
  void				setKeyUpPlayer1();
  int				getKeyDownPlayer1() const;
  void				setKeyDownPlayer1();
  int				getKeyRightPlayer1() const;
  void				setKeyRightPlayer1();
  int				getKeyLeftPlayer1() const;
  void				setKeyLeftPlayer1();
  int				getKeyBombPlayer1() const;
  void				setKeyBombPlayer1();
  int				getKeyUpPlayer2() const;
  void				setKeyUpPlayer2();
  int				getKeyDownPlayer2() const;
  void				setKeyDownPlayer2();
  int				getKeyRightPlayer2() const;
  void				setKeyRightPlayer2();
  int				getKeyLeftPlayer2() const;
  void				setKeyLeftPlayer2();
  int				getKeyBombPlayer2() const;
  void				setKeyBombPlayer2();
  const std::string             &getBackup() const;
  void                          setBackup();
private:
  bool				_save;
  bool				_quit;
  bool				_play;
  std::string			_mapChoosen;
  int				_mapLenght;
  int				_mapWidth;
  bool				_twoPlayers;
  int				_nbIaPlayers;
  int				_iaDifficulty;
  int				_effectsSound;
  int				_musicSound;
  std::string			_loadGame;
  int				_keyUpPlayer[2];
  int				_keyDownPlayer[2];
  int				_keyRightPlayer[2];
  int				_keyLeftPlayer[2];
  int				_keyBombPlayer[2];
  std::string			_namePlayer[2];
  std::string			_backup;
};

#endif
