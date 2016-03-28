//
// Player.hh for Player.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May  7 17:19:01 2014 CHAUCHET Alan
// Last update Fri Jun  6 10:01:09 2014 CHAUCHET Alan
//

#ifndef			PLAYER_HH_
# define		PLAYER_HH_

# include		"Game/BomberGame.hh"

typedef bool		(BomberGame::*recupNewAction)(e_action &);

class	Player;

typedef void		(Player::*execAction)(e_action);

class			Player : public APlayer
{
  std::string		_name;
  BomberGame		*_game;
  Cond			*_condAction;
  recupNewAction	_getAction;
  execAction		_tabAction[6];

public:
  Player(BomberGame *, e_playerType, double, double);
  virtual ~Player();
  virtual void		play(void);
  void			callMove(e_action);
  void			callPutBomb(e_action);
  void			callDie(e_action);
  void			setName(const std::string &);
  const std::string	&getName(void) const;
};

#endif			/* PLAYER_HH_ */
