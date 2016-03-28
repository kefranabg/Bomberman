//
// Map.cpp for Map.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Fri May 23 15:46:00 2014 CHAUCHET Alan
// Last update Sun Jun  8 12:15:15 2014 CHAUCHET Alan
//

#include			"Game/Map.hh"
#include			"Game/APlayer.hh"
#include			"Game/Rand.hh"

Map::Map(unsigned int x, unsigned int y)
{
  this->_sizeX = x + 2;
  this->_sizeY = y + 2;
  for (unsigned int count = 0; count < ((x + 2) * (y + 2)); count++)
    this->_boxs.push_back(new Box((count % (x + 2)), (count / (x + 2))));
}

Map::Map(const Map &copy)
{
  this->_sizeX = copy._sizeX;
  this->_sizeY = copy._sizeY;
  for (unsigned int i = 0; i < copy._boxs.size(); ++i)
    this->_boxs.push_back(new Box(*copy._boxs[i]));
}

Map::Map(unsigned int x, unsigned int y, const std::vector<Box *> &boxs)
{
  this->_sizeX = x;
  this->_sizeY = y;
  for (unsigned int i = 0; i < boxs.size(); ++i)
    this->_boxs.push_back(new Box(*boxs[i]));
}

Map::~Map()
{
  for (unsigned int count = 0; count < this->_boxs.size(); ++count)
    delete(this->_boxs[count]);
  this->_boxs.clear();
}

bool				Map::takeObj(unsigned int x, unsigned int y, e_typeObj obj) const
{
  if (POS_TAB(x, y, this->_sizeX) >= this->_boxs.size() || x >= this->_sizeX || y >= this->_sizeY)
    return (false);
  return (this->_boxs[POS_TAB(x, y, this->_sizeX)]->takeObj(obj));
}

bool				Map::addObj(unsigned int x, unsigned int y, e_typeObj obj, bool &destroyed)
{
  destroyed = false;
  if (POS_TAB(x, y, this->_sizeX) >= this->_boxs.size() || x >= this->_sizeX || y >= this->_sizeY)
    return (true);
  return (this->_boxs[POS_TAB(x, y, this->_sizeX)]->addObj(obj, destroyed));
}

const std::vector<e_typeObj>	&Map::getObj(unsigned int x, unsigned int y) const
{
  if (POS_TAB(x, y, this->_sizeX) >= this->_boxs.size() || x >= this->_sizeX || y >= this->_sizeY)
    return (this->_boxs[0]->getObj());
  return (this->_boxs[POS_TAB(x, y, this->_sizeX)]->getObj());
}

const std::vector<Box *>	&Map::getBoxs(void) const {
  return (this->_boxs);
}


bool				Map::isObstacle(unsigned int x, unsigned int y) const
{
  if (POS_TAB(x, y, this->_sizeX) >= this->_boxs.size() || x >= this->_sizeX || y >= this->_sizeY)
    return (true);
  return (this->_boxs[POS_TAB(x, y, this->_sizeX)]->isObstacle());
}

bool				Map::isFire(unsigned int x, unsigned int y) const
{
  if (POS_TAB(x, y, this->_sizeX) >= this->_boxs.size() || x >= this->_sizeX || y >= this->_sizeY)
    return (false);
  return (this->_boxs[POS_TAB(x, y, this->_sizeX)]->isFire());
}

bool				Map::isBonus(unsigned int x, unsigned int y) const
{
  if (POS_TAB(x, y, this->_sizeX) >= this->_boxs.size() || x >= this->_sizeX || y >= this->_sizeY)
    return (false);
  return (this->_boxs[POS_TAB(x, y, this->_sizeX)]->isBonus());
}

bool				Map::isBomb(unsigned int x, unsigned int y) const
{
  if (POS_TAB(x, y, this->_sizeX) >= this->_boxs.size() || x >= this->_sizeX || y >= this->_sizeY)
    return (false);
  return (this->_boxs[POS_TAB(x, y, this->_sizeX)]->isBomb());
}

bool				Map::isWallD(unsigned int x, unsigned int y) const
{
  if (POS_TAB(x, y, this->_sizeX) >= this->_boxs.size() || x >= this->_sizeX || y >= this->_sizeY)
    return (false);
  return (this->_boxs[POS_TAB(x, y, this->_sizeX)]->isWallD());
}

bool				Map::isWallI(unsigned int x, unsigned int y) const
{
  if (POS_TAB(x, y, this->_sizeX) >= this->_boxs.size() || x >= this->_sizeX || y >= this->_sizeY)
    return (false);
  return (this->_boxs[POS_TAB(x, y, this->_sizeX)]->isWallI());
}

bool				Map::takeBonus(unsigned int x, unsigned int y, e_typeObj &bonus) const
{
  if (this->takeObj(x, y, BONUS_NEW_BOMB))
    {
      bonus = BONUS_NEW_BOMB;
      return (true);
    }
  if (this->takeObj(x, y, BONUS_ADD_RANGE))
    {
      bonus = BONUS_ADD_RANGE;
      return (true);
    }
  if (this->takeObj(x, y, BONUS_SPEED_UP))
    {
      bonus = BONUS_SPEED_UP;
      return (true);
    }
  return (false);
}

unsigned int			Map::getSizeX(void) const
{
  return (this->_sizeX);
}

unsigned int			Map::getSizeY(void) const
{
  return (this->_sizeY);
}

void				Map::fillMap(std::vector<APlayer *> const &players)
{
  unsigned int			nb;
  Rand				myRand;
  bool				good;
  bool				destroyed;

  for (unsigned int count = 0; count < this->_sizeX; ++count)
    {
      this->addObj(count, 0, WALL_I, destroyed);
      this->addObj(count, this->_sizeY - 1, WALL_I, destroyed);
    }
  for (unsigned int count = 0; count < this->_sizeY; ++count)
    {
      this->addObj(0, count, WALL_I, destroyed);
      this->addObj(this->_sizeX - 1, count, WALL_I, destroyed);
    }
  for (unsigned int county = 1; county < this->_sizeY - 1; ++county)
    {
      for (unsigned int countx = 1; countx < this->_sizeX - 1; ++countx)
	{
	  good = true;
	  for (unsigned int tmp = 0; tmp < players.size() ; ++tmp)
	    if ((static_cast<unsigned int>(players[tmp]->getPosX()) == countx &&
		 static_cast<unsigned int>(players[tmp]->getPosY()) == county) ||
		(static_cast<unsigned int>(players[tmp]->getPosX()) == countx - 1 &&
		 static_cast<unsigned int>(players[tmp]->getPosY()) == county) ||
		(static_cast<unsigned int>(players[tmp]->getPosX()) == countx + 1 &&
		 static_cast<unsigned int>(players[tmp]->getPosY()) == county) ||
		(static_cast<unsigned int>(players[tmp]->getPosX()) == countx &&
		 static_cast<unsigned int>(players[tmp]->getPosY()) == county - 1) ||
		(static_cast<unsigned int>(players[tmp]->getPosX()) == countx &&
		 static_cast<unsigned int>(players[tmp]->getPosY()) == county + 1))
	      good = false;
	  if (good == true)
	    {
	      nb = myRand.rand(0, 6);
	      if (nb < 1)
		this->addObj(countx, county, WALL_I, destroyed);
	      if (nb >= 1 && nb < 5)
		{
		  this->addObj(countx, county, WALL_D, destroyed);
		  nb = myRand.rand(0, 2);
		  if (nb == 1)
		    {
		      nb = myRand.rand(0, 4);
		      if (nb == 0)
			this->addObj(countx, county, BONUS_NEW_BOMB, destroyed);
		      if (nb == 1)
			this->addObj(countx, county, BONUS_ADD_RANGE, destroyed);
		      if (nb == 2)
			this->addObj(countx, county, BONUS_SPEED_UP, destroyed);
		    }
		}
	    }
	}
    }
}

Map			&Map::operator=(const Map &copy)
{
  this->_sizeX = copy._sizeX;
  this->_sizeY = copy._sizeY;
  this->_boxs.clear();
  for (unsigned int i = 0; i < copy._boxs.size(); ++i)
    this->_boxs.push_back(new Box(*copy._boxs[i]));
  return (*this);
}

bool			Map::operator==(const Map &cmp) const
{
  if (this->_sizeX != cmp._sizeX || this->_sizeY != cmp._sizeY)
    return (false);
  for (unsigned int count = 0; count < this->_boxs.size(); count++)
    if (!(*(this->_boxs[count]) == *(cmp._boxs[count])))
      return (false);
  return (true);
}

Box			&Map::operator[](int pos) const
{
  return (*(this->_boxs[pos]));
}
