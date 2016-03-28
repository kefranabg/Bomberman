//
// BomberGame.hh for BomberGame.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May 21 11:57:37 2014 CHAUCHET Alan
// Last update Fri Jun 13 15:02:21 2014 Maxime Manzano
//

#ifndef				BOMBERGAME_HH_
# define			BOMBERGAME_HH_

# include			<iostream>
# include			<vector>
# include			"APlayer.hh"
# include			"Map.hh"

class				Window;
class				MenuGUI;
class				MapGUI;
class				Cinematic;

typedef enum			e_winner
  {
    PLAYER1_WIN			= 0,
    PLAYER2_WIN			= 1,
    IA_WIN			= 2,
    NOBODY			= 3
  }				e_winner;

class				Player;

class				BomberGame
{
  bool				_anim;
  bool				_isPlayer2;
  std::vector<APlayer *>	_players;
  std::vector<e_action>		_actionPlayer1;
  std::vector<e_action>		_actionPlayer2;
  Mutex				_mutexPlayer1;
  Mutex				_mutexPlayer2;
  Cond				_condPlayer1;
  Cond				_condPlayer2;
  Cond				_condBomb;
  Map				*_map;
  bool				_quit;
  bool				_stop;
  Window			*_window;
  MenuGUI			*_menuGUI;
  MapGUI			*_mapGUI;
  Cinematic			*_cinematic;
  bool				_isPaused;
  e_winner			_winner;
  std::vector<std::string>	_scoreNames;
  std::vector<unsigned int>	_scoreValues;
  std::string			_winnerName;

public:
  BomberGame();
  ~BomberGame();
  void				createMap(unsigned int, unsigned int);
  void				createMap(unsigned int, unsigned int, const std::vector<Box *> &);
  void				addActionPlayer1(e_action);
  void				addActionPlayer2(e_action);
  bool				takeActionPlayer1(e_action &);
  bool				takeActionPlayer2(e_action &);
  void				emptyActionPlayer1(void);
  void				emptyActionPlayer2(void);
  Cond				*getCondAction(e_playerType);
  Map				*getMap(void);
  Cond				*getCondBomb(void);
  bool				getIsPlayer2(void) const;
  void				setIsPlayer2(bool);
  void				createPlayers(bool, unsigned int, int);
  void				createPlayersLoadMap(bool, unsigned int, int);
  void				launchPlayers(void) const;
  std::vector<APlayer *>	*getPlayersAccess(void);
  void				save(const std::string &);
  void				load(const std::string &, bool isSave = true);
  void				fillMap(void) const;
  void				setQuit(bool);
  void				start(void);
  void				play(void);
  void				pause(void);
  void				unpause(void);
  void				deleteGame(void);
  bool				checkPlayers(void);
  void				affError(const std::string &, bool &) const;
  bool				isPaused(void) const;
  Player			*getPlayer(e_playerType) const;
  void				loadScore(void);
  void				saveScore(void) const;
  void				setAnim(bool);
  bool				getAnim(void) const;
  void				changeScore(void);
  void				setWinnerName();
};

#endif
