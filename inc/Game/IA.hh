//
// IA.hh for IA.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May  7 17:19:01 2014 CHAUCHET Alan
// Last update Fri Jun 13 18:31:50 2014 CHAUCHET Alan
//

#ifndef			IA_HH_
# define		IA_HH_

# include		"APlayer.hh"

# define		INT_DEFAULT		-5
# define		INT_WALLI		-4
# define		INT_WALLD		-3
# define		INT_POS_IA		0
# define		INT_PLAYER		1
# define		INT_BOMB		-2
# define		INT_FIRE		-1
# define		INT_BONUS		2

# define		LEE_DEFAULT		-2
# define		LEE_WALLI		-1
# define		LEE_WALLD		-1
# define		LEE_BOMB		-1
# define		LEE_FIRE		-42

class			IA : public APlayer
{
private:
  int			_difficulty;
  std::vector<APlayer*>	*_players;
  int			_goToX;
  int			_goToY;
  e_direction		_goTo;
  bool			_forceBomb;

public:
  IA(BomberGame *, double, double, int, std::vector<APlayer *> *);
  virtual ~IA();
  virtual void		play(void);
  int			getDifficulty(void) const;
  void			fillMapOfInt(std::vector<int> &, int) const;
  void			putWallIOnMap(std::vector<int> &, int) const;
  void			putWallDOnMap(std::vector<int> &, int) const;
  void			putBombOnMap(std::vector<int> &, int, int) const;
  void			putIntOnMap(std::vector<int> &, int, int, int) const;
  void			putPlayerOnMap(std::vector<int> &, int) const;
  void			putBonusOnMap(std::vector<int> &, int) const;
  void			putLeeAlgorithm(std::vector<int> &) const;
  void			fillLeeWay(std::vector<int> &, unsigned int, unsigned int, int) const;
  bool			isSafe(std::vector<int> &) const;
  void			findSafePlace(std::vector<int> &, std::vector<int> &);
  bool			isReachable(std::vector<int> &, int, int) const;
  void			selectDirection(std::vector<int> &);
  bool			isEnnemyAround(std::vector<int> &) const;
  bool			findBonus(std::vector<int> &, std::vector<int> &);
  bool			findWall(std::vector<int> &, std::vector<int> &);
  bool			findEnnemy(std::vector<int> &, std::vector<int> &);
};

#endif			/* IA_HH_ */
