//
// Player.cpp for Player.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Sat May 10 16:46:38 2014 LOEB Thomas
// Last update Fri Jun  6 10:00:59 2014 CHAUCHET Alan
//

#include		"Game/Player.hh"

Player::Player(BomberGame *game, e_playerType type, double posX, double posY) : APlayer(game, type, posX, posY)
{
  this->_condAction = game->getCondAction(type);
  this->_game = game;
  if (type == PLAYER1)
    this->_getAction = &BomberGame::takeActionPlayer1;
  else
    this->_getAction = &BomberGame::takeActionPlayer2;
  this->_tabAction[0] = &Player::callMove;
  this->_tabAction[1] = &Player::callMove;
  this->_tabAction[2] = &Player::callMove;
  this->_tabAction[3] = &Player::callMove;
  this->_tabAction[4] = &Player::callPutBomb;
  this->_tabAction[5] = &Player::callDie;
}

Player::~Player()
{
}

void			Player::play(void)
{
  e_action	action;

  while (this->_isAlive)
    {
      if (!(this->_game->*this->_getAction)(action))
	this->_condAction->timedwait(0, 1000000);
      else
	(this->*this->_tabAction[static_cast<int>(action)])(action);
      this->checkMap();
    }
  this->_thread.exit(NULL);
}

void			Player::callMove(e_action action)
{
  this->move(static_cast<e_direction>(action));
}

void			Player::callPutBomb(e_action action)
{
  static_cast<void>(action);
  this->putBomb();
}

void			Player::callDie(e_action action)
{
  static_cast<void>(action);
  this->die();
}

void			Player::setName(const std::string &name)
{
  this->_name = name;
}

const std::string	&Player::getName(void) const
{
  return (this->_name);
}
