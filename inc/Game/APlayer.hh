//
// APlayer.hh for APlayer.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May  7 17:19:01 2014 CHAUCHET Alan
// Last update Thu Jun 12 15:53:34 2014 CHAUCHET Alan
//

#ifndef			APLAYER_HH_
# define		APLAYER_HH_

# include		"Game/Bomb.hh"
# include		"Thread/Mutex.hh"
# include		"Thread/Thread.hh"
# include		"Game/Map.hh"

class			MapGUI;
class			PlayerGUI;

typedef enum		e_playerType
  {
    PLAYER1		= 0,
    PLAYER2		= 1,
    PLAYERIA		= 2
  }			e_playerType;

typedef enum		e_direction
  {
    UP			= 0,
    DOWN		= 1,
    LEFT		= 2,
    RIGHT		= 3,
    NO_DIRECTION	= 4
  }			e_direction;

typedef enum		e_action
  {
    MOVE_UP		= 0,
    MOVE_DOWN		= 1,
    MOVE_LEFT		= 2,
    MOVE_RIGHT		= 3,
    PUT_BOMB		= 4,
    DIE			= 5,
    DO_NOTHING		= 6
  }			e_action;

class			BomberGame;

class			APlayer
{
  typedef void		(APlayer::*functionBonus)(void);

protected:
  Thread		_thread;
  bool			_isAlive;
  e_playerType		_type;
  std::vector<Bomb *>	_bombs;
  double		_speed;
  double		_posX;
  double		_posY;
  Map			*_map;
  Cond			*_cond;
  Mutex			_scoreMutex;
  unsigned int		_score;
  int			incrMove[2][4];
  unsigned int		_rangeBomb;
  functionBonus		_takeBonus[3];

public:
  APlayer(BomberGame *, e_playerType, double, double);
  virtual ~APlayer();
  static int		round(double);
  void			addBomb(void);
  void			increaseBombRange(void);
  void			increaseSpeed(void);
  void			putBomb(void);
  void			move(e_direction);
  void			die(void);
  e_playerType		getType(void) const;
  bool			isAlive(void) const;
  void			launch(void);
  void			checkMap(void);
  virtual void		play(void) = 0;
  double		getPosX(void) const;
  double		getPosY(void) const;
  void			setRangeBomb(unsigned int);
  unsigned int		getRangeBomb(void) const;
  void			setSpeed(double);
  double		getSpeed(void) const;
  void			setScore(unsigned int);
  unsigned int		getScore(void) const;
  unsigned int		getNbBombs(void) const;
  unsigned int		getNbBombsAvailable(void) const;
  void			pauseBombs(void) const;
  void			unpauseBombs(void) const;
  void			killBombs(void);
  void			setMap(Map *);
  void			reset(void);
};

void			*launchPlayer(void *);

#endif			/* APLAYER_HH_ */
