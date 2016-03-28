//
// Map.hh for Map.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May  7 17:19:01 2014 CHAUCHET Alan
// Last update Sun Jun  8 12:14:52 2014 CHAUCHET Alan
//

#ifndef					MAP_HH_
# define				MAP_HH_

# include				"Box.hh"

# define				POS_TAB(x, y, size)		((y) * (size) + (x))

class					APlayer;

class					Map
{
  std::vector<Box *>			_boxs;
  unsigned int				_sizeX;
  unsigned int				_sizeY;

public:
  Map(unsigned int, unsigned int);
  Map(unsigned int, unsigned int, const std::vector<Box *> &);
  Map(const Map &);
  ~Map();
  bool					takeObj(unsigned int, unsigned int, e_typeObj) const;
  bool					addObj(unsigned int, unsigned int, e_typeObj, bool &destroyed);
  const std::vector<e_typeObj>		&getObj(unsigned int, unsigned int) const;
  const std::vector<Box *>		&getBoxs(void) const;
  bool					isObstacle(unsigned int, unsigned int) const;
  bool					isFire(unsigned int, unsigned int) const;
  bool					isBonus(unsigned int, unsigned int) const;
  bool					isBomb(unsigned int, unsigned int) const;
  bool					isWallD(unsigned int, unsigned int) const;
  bool					isWallI(unsigned int, unsigned int) const;
  bool					takeBonus(unsigned int, unsigned int, e_typeObj &) const;
  unsigned int				getSizeX(void) const;
  unsigned int				getSizeY(void) const;
  void					printMap(void) const;
  void					fillMap(std::vector<APlayer *> const &);
  Map					&operator=(const Map &);
  bool					operator==(const Map &) const;
  Box					&operator[](int) const;
};

#endif
