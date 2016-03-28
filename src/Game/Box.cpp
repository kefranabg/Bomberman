//
// Box.cpp for Box.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Sat May 10 12:04:11 2014 CHAUCHET Alan
// Last update Sun Jun  8 12:15:33 2014 CHAUCHET Alan
//

#include			"Game/Box.hh"

Box::Box(int x, int y)
{
  this->_posX = x;
  this->_posY = y;
  this->_mutex.create();
}

Box::Box(const Box &copy)
{
  this->_posX = copy._posX;
  this->_posY = copy._posY;
  this->_obj = copy._obj;
  this->_mutex.create();
}

Box::~Box()
{
  this->_mutex.destroy();
}

const std::vector<e_typeObj>	&Box::getObj(void) const
{
  return (this->_obj);
}

bool				Box::addObj(e_typeObj obj, bool &destroyed)
{
  this->_mutex.lock();
  for (unsigned int count = 0; count < this->_obj.size(); count++)
    {
      if (this->_obj[count] == obj && obj != FIRE)
	{
	  this->_mutex.unlock();
	  return (true);
	}
      if (this->_obj[count] == WALL_I)
	{
	  this->_mutex.unlock();
	  return (false);
	}
    }
  this->_obj.push_back(obj);
  this->_mutex.unlock();
  destroyed = false;
  if (obj == FIRE)
    {
      if (this->takeObj(WALL_D))
	{
	  destroyed = true;
	  return (false);
	}
    }
  return (true);
}

bool				Box::takeObj(e_typeObj obj)
{
  this->_mutex.lock();
  for (unsigned int count = 0; count < this->_obj.size(); count++)
    if (this->_obj[count] == obj)
      {
	this->_obj.erase(this->_obj.begin() + count);
	this->_mutex.unlock();
	return (true);
      }
  this->_mutex.unlock();
  return (false);
}

bool				Box::isObstacle(void)
{
  this->_mutex.lock();
  for (unsigned int count = 0; count < this->_obj.size(); count++)
    if (this->_obj[count] == WALL_D || this->_obj[count] == WALL_I
	|| this->_obj[count] == BOMB)
      {
	this->_mutex.unlock();
	return (true);
      }
  this->_mutex.unlock();
  return (false);
}

bool				Box::isFire(void)
{
  this->_mutex.lock();
  for (unsigned int count = 0; count < this->_obj.size(); count++)
    if (this->_obj[count] == FIRE)
      {
	this->_mutex.unlock();
	return (true);
      }
  this->_mutex.unlock();
  return (false);
}

bool				Box::isBonus(void)
{
  this->_mutex.lock();
  for (unsigned int count = 0; count < this->_obj.size(); count++)
    if (this->_obj[count] == BONUS_NEW_BOMB || this->_obj[count] == BONUS_SPEED_UP
	|| this->_obj[count] == BONUS_ADD_RANGE)
      {
	this->_mutex.unlock();
	return (true);
      }
  this->_mutex.unlock();
  return (false);
}

bool				Box::isBomb(void)
{
  this->_mutex.lock();
  for (unsigned int count = 0; count < this->_obj.size(); count++)
    if (this->_obj[count] == BOMB)
      {
	this->_mutex.unlock();
	return (true);
      }
  this->_mutex.unlock();
  return (false);
}

bool				Box::isWallD(void)
{
  this->_mutex.lock();
  for (unsigned int count = 0; count < this->_obj.size(); count++)
    if (this->_obj[count] == WALL_D)
      {
	this->_mutex.unlock();
	return (true);
      }
  this->_mutex.unlock();
  return (false);
}

bool				Box::isWallI(void)
{
  this->_mutex.lock();
  for (unsigned int count = 0; count < this->_obj.size(); count++)
    if (this->_obj[count] == WALL_I)
      {
	this->_mutex.unlock();
	return (true);
      }
  this->_mutex.unlock();
  return (false);
}

int				Box::getPosX(void) const
{
  return (this->_posX);
}

int				Box::getPosY(void) const
{
  return (this->_posY);
}

Box				&Box::operator=(const Box &copy)
{
  this->_posX = copy._posX;
  this->_posY = copy._posY;
  this->_obj = copy._obj;
  return (*this);
}

bool				Box::operator==(const Box &cmp) const
{
  return ((this->_obj == cmp._obj));
}
