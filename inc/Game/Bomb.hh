//
// Bomb.hh for Bomb.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May  7 17:19:01 2014 CHAUCHET Alan
// Last update Thu Jun  5 15:48:54 2014 CHAUCHET Alan
//

#ifndef			BOMB_HH_
# define		BOMB_HH_

# include		<iostream>
# include		<unistd.h>
# include		<time.h>
# include		<sys/timeb.h>
# include		"../Thread/Thread.hh"
# include		"../Thread/Mutex.hh"
# include		"../Thread/Cond.hh"
# include		"Map.hh"
# include		"Bomb.hh"

class			APlayer;

class			Bomb
{
  APlayer		*_player;
  Thread		_thread;
  Mutex			_mutex;
  Cond			*_cond;
  Map			*_map;
  bool			_isActiv;
  int			_posX;
  int			_posY;
  unsigned int		_range;
  long			_timeToBomb;
  bool			_pause;
  bool			_stop;

public:
  Bomb(Map *, Cond *, APlayer *);
  ~Bomb();
  void			setRange(unsigned int);
  unsigned int		getRange(void) const;
  void			setTimeToBomb(long);
  long			getTimeToBomb(void) const;
  void			put(void);
  bool			launch(int, int);
  void			setPause(bool);
  bool			getPause(void) const;
  void			pause(void);
  void			unpause(void);
  void			stop(void);
  bool			isActiv(void) const;
  void			setMap(Map *);
};

void			*callPut(void *);

#endif
