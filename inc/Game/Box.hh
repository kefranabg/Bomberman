//
// Box.hh for Box.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May  7 17:19:01 2014 CHAUCHET Alan
// Last update Sun Jun  8 12:14:59 2014 CHAUCHET Alan
//

#ifndef					BOX_HH_
# define				BOX_HH_

# include				<iostream>
# include				<vector>
# include				"Thread/Mutex.hh"

typedef enum				e_typeObj
  {
    WALL_D				= 0,
    WALL_I				= 1,
    BONUS_NEW_BOMB			= 2,
    BONUS_ADD_RANGE			= 3,
    BONUS_SPEED_UP			= 4,
    FIRE				= 5,
    BOMB				= 6
  }					e_typeObj;

class					Box
{
  int					_posX;
  int					_posY;
  std::vector<e_typeObj>		_obj;
  Mutex					_mutex;

public:
  Box(int, int);
  Box(const Box &);
  ~Box();
  const std::vector<e_typeObj>		&getObj(void) const;
  bool					addObj(e_typeObj, bool &destroyed);
  bool					takeObj(e_typeObj);
  bool					isObstacle(void);
  bool					isFire(void);
  bool					isBonus(void);
  bool					isBomb(void);
  bool					isWallD(void);
  bool					isWallI(void);
  int					getPosX(void) const;
  int					getPosY(void) const;
  Box					&operator=(const Box &);
  bool					operator==(const Box &) const;
};

#endif
