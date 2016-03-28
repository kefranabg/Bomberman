//
// IA.cpp for IA.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Sat May 10 16:43:51 2014 LOEB Thomas
// Last update Fri Jun 13 18:40:55 2014 CHAUCHET Alan
//

#include			"Game/IA.hh"

IA::IA(BomberGame *game, double posX, double posY, int difficulty, std::vector<APlayer *> *players) : APlayer(game, PLAYERIA, posX, posY), _difficulty(difficulty), _players(players)
{
  _forceBomb = false;
}

IA::~IA()
{
}

void				IA::play(void)
{
  std::vector<int>		mapOfInt;
  std::vector<int>		mapOfLee;
  int				lastX;
  int				lastY;

  mapOfInt.resize(this->_map->getSizeX() * this->_map->getSizeY());
  mapOfLee.resize(this->_map->getSizeX() * this->_map->getSizeY());
  while (this->_isAlive)
    {
      this->_goToX = -1;
      this->_goToY = -1;
      this->_goTo = NO_DIRECTION;
      lastX = APlayer::round(this->_posX);
      lastY = APlayer::round(this->_posY);

      this->fillMapOfInt(mapOfInt, INT_DEFAULT);
      this->putBonusOnMap(mapOfInt, INT_BONUS);
      this->putWallIOnMap(mapOfInt, INT_WALLI);
      this->putWallDOnMap(mapOfInt, INT_WALLD);
      this->putPlayerOnMap(mapOfInt, INT_PLAYER);
      this->putBombOnMap(mapOfInt, INT_BOMB, INT_FIRE);

      this->fillMapOfInt(mapOfLee, LEE_DEFAULT);
      this->putBombOnMap(mapOfLee, LEE_BOMB, LEE_FIRE);
      this->putWallIOnMap(mapOfLee, LEE_WALLI);
      this->putWallDOnMap(mapOfLee, LEE_WALLD);
      this->putLeeAlgorithm(mapOfLee);

      if (!this->isSafe(mapOfInt))
	this->findSafePlace(mapOfInt, mapOfLee);
      else if (this->_difficulty >= 1)
	  if (!this->findBonus(mapOfInt, mapOfLee) && this->getNbBombsAvailable() > 0)
	    {
	      if (this->isEnnemyAround(mapOfInt))
		this->putBomb();
	      else if (this->_difficulty >= 2 && !this->findWall(mapOfInt, mapOfLee))
		this->findEnnemy(mapOfInt, mapOfLee);
	    }
      this->selectDirection(mapOfLee);
      if ((this->_goToX != lastX ||
	   this->_goToY != lastY)
	  && this->_goToX != -1 && this->_goToY != -1
	  && this->_goTo != NO_DIRECTION)
	{
	  move(this->_goTo);
	  usleep(20000);
	}
      else if (_forceBomb)
	{
	  _forceBomb = false;
	  this->putBomb();
	}
      this->checkMap();
    }
  this->_thread.exit(NULL);
}

void				IA::fillMapOfInt(std::vector<int> &mapOfInt, int value) const
{
  for (unsigned int count = 0; count < mapOfInt.size(); ++count)
    mapOfInt[count] = value;
}

void				IA::putWallIOnMap(std::vector<int> &mapOfInt, int value) const
{
  for (unsigned int count = 0; count < mapOfInt.size(); ++count)
    if ((*(this->_map))[count].isWallI())
      mapOfInt[count] = value;
}

void				IA::putWallDOnMap(std::vector<int> &mapOfInt, int value) const
{
  for (unsigned int count = 0; count < mapOfInt.size(); ++count)
    if ((*(this->_map))[count].isWallD())
      mapOfInt[count] = value;
}

void				IA::putBonusOnMap(std::vector<int> &mapOfInt, int value) const
{
  for (unsigned int count = 0; count < mapOfInt.size(); ++count)
    if ((*(this->_map))[count].isBonus())
      mapOfInt[count] = value;
}

void				IA::putBombOnMap(std::vector<int> &mapOfInt, int valueBomb, int valueFire) const
{
  bool				left = true;
  bool				right = true;
  bool				up = true;
  bool				down = true;
  int				x;
  int				y;

  for (unsigned int count = 0; count < mapOfInt.size(); ++count)
    if ((*(this->_map))[count].isBomb())
      {
	x = count % this->_map->getSizeX();
	y = count / this->_map->getSizeX();

	left = true;
	right = true;
	up = true;
	down = true;
	if (valueFire != LEE_FIRE)
	  for (int count2 = 1; count2 <= static_cast<int>(this->_rangeBomb); ++count2)
	    {
	      if (left && x + count2 < static_cast<int>(this->_map->getSizeX()))
		{
		  if (mapOfInt[POS_TAB(x + count2, y, this->_map->getSizeX())] == INT_WALLI
		      || mapOfInt[POS_TAB(x + count2, y, this->_map->getSizeX())] == INT_WALLD)
		    left = false;
		  else
		    mapOfInt[POS_TAB(x + count2, y, this->_map->getSizeX())] = valueFire;
		}
	      if (right && x - count2 >= 0)
		{
		  if (mapOfInt[POS_TAB(x - count2, y, this->_map->getSizeX())] == INT_WALLI
		      || mapOfInt[POS_TAB(x - count2, y, this->_map->getSizeX())] == INT_WALLD)
		    right = false;
		  else
		    mapOfInt[POS_TAB(x - count2, y, this->_map->getSizeX())] = valueFire;
		}
	      if (up && y + count2 < static_cast<int>(this->_map->getSizeY()))
		{
		  if (mapOfInt[POS_TAB(x, y + count2, this->_map->getSizeX())] == INT_WALLI
		      || mapOfInt[POS_TAB(x, y + count2, this->_map->getSizeX())] == INT_WALLD)
		    up = false;
		  else
		    mapOfInt[POS_TAB(x, y + count2, this->_map->getSizeX())] = valueFire;
		}
	      if (down && y - count2 >= 0)
		{
		  if (mapOfInt[POS_TAB(x, y - count2, this->_map->getSizeX())] == INT_WALLI
		      || mapOfInt[POS_TAB(x, y - count2, this->_map->getSizeX())] == INT_WALLD)
		    down = false;
		  else
		    mapOfInt[POS_TAB(x, y - count2, this->_map->getSizeX())] = valueFire;
		}
	    }
	mapOfInt[count] = valueBomb;
      }
    else if ((*(this->_map))[count].isFire() && valueFire == LEE_FIRE)
      mapOfInt[count] = valueBomb;
}

void				IA::putIntOnMap(std::vector<int> &mapOfInt, int x, int y, int value) const
{
  mapOfInt[POS_TAB(x, y, this->_map->getSizeX())] = value;
}

int				IA::getDifficulty(void) const
{
  return (this->_difficulty);
}

void				IA::putPlayerOnMap(std::vector<int> &mapOfInt, int value) const
{
  for (unsigned int count = 0; count < this->_players->size(); ++count)
    if ((*(this->_players))[count] != this)
      mapOfInt[POS_TAB(APlayer::round((*(this->_players))[count]->getPosX()), APlayer::round((*(this->_players))[count]->getPosY()), this->_map->getSizeX())] = value;
}

void				IA::putLeeAlgorithm(std::vector<int> &mapOfLee) const
{
  mapOfLee[POS_TAB(APlayer::round(this->_posX), APlayer::round(this->_posY), this->_map->getSizeX())] = 0;
  fillLeeWay(mapOfLee, APlayer::round(this->_posX), APlayer::round(this->_posY), 1);
}

void				IA::fillLeeWay(std::vector<int> &mapOfLee, unsigned int x, unsigned int y, int value) const
{
  if (x + 1 < this->_map->getSizeX() && !this->_map->isObstacle(x + 1, y)
      && (mapOfLee[POS_TAB(x + 1, y, this->_map->getSizeX())] == LEE_DEFAULT
	  || mapOfLee[POS_TAB(x + 1, y, this->_map->getSizeX())] > value))
    {
      mapOfLee[POS_TAB(x + 1, y, this->_map->getSizeX())] = value;
      this->fillLeeWay(mapOfLee, x + 1, y, value + 1);
    }
  if (x > 0 && !this->_map->isObstacle(x - 1, y)
      && (mapOfLee[POS_TAB(x - 1, y, this->_map->getSizeX())] == LEE_DEFAULT
	  || mapOfLee[POS_TAB(x - 1, y, this->_map->getSizeX())] > value))
    {
      mapOfLee[POS_TAB(x - 1, y, this->_map->getSizeX())] = value;
      this->fillLeeWay(mapOfLee, x - 1, y, value + 1);
    }
  if (y + 1 < this->_map->getSizeY() && !this->_map->isObstacle(x, y + 1)
      && (mapOfLee[POS_TAB(x, y + 1, this->_map->getSizeX())] == LEE_DEFAULT
	  || mapOfLee[POS_TAB(x, y + 1, this->_map->getSizeX())] > value))
    {
      mapOfLee[POS_TAB(x, y + 1, this->_map->getSizeX())] = value;
      this->fillLeeWay(mapOfLee, x, y + 1, value + 1);
    }
  if (y > 0 && !this->_map->isObstacle(x, y - 1)
      && (mapOfLee[POS_TAB(x, y - 1, this->_map->getSizeX())] == LEE_DEFAULT
	  || mapOfLee[POS_TAB(x, y - 1, this->_map->getSizeX())] > value))
    {
      mapOfLee[POS_TAB(x, y - 1, this->_map->getSizeX())] = value;
      this->fillLeeWay(mapOfLee, x, y - 1, value + 1);
    }
}

bool				IA::isSafe(std::vector<int> &mapOfInt) const
{
  int				posX = APlayer::round(this->_posX);
  int				posY = APlayer::round(this->_posY);

  if (mapOfInt[POS_TAB(posX, posY, this->_map->getSizeX())] == INT_BOMB
      || mapOfInt[POS_TAB(posX, posY, this->_map->getSizeX())] == INT_FIRE)
    return (false);
  return (true);
}

void				IA::findSafePlace(std::vector<int> &mapOfInt, std::vector<int> &mapOfLee)
{
  int				closest = -1;

  for (unsigned int count = 0; count < mapOfLee.size(); ++count)
    {
      if (mapOfLee[count] >= 0
	  && (mapOfLee[count] < closest || closest == -1)
	  && mapOfInt[count] != INT_FIRE && mapOfInt[count] != INT_BOMB)
	{
	  closest = mapOfLee[count];
	  this->_goToX = count % this->_map->getSizeX();
	  this->_goToY = count / this->_map->getSizeX();
	}
    }
}

bool				IA::isReachable(std::vector<int> &mapOfLee, int x, int y) const
{
  if (mapOfLee[POS_TAB(x, y, this->_map->getSizeX())] >= 0)
    return (true);
  return (false);
}

void				IA::selectDirection(std::vector<int> &mapOfLee)
{
  int				x = this->_goToX;
  int				y = this->_goToY;
  int				value;

  if (x == -1 || y == -1 ||
      (x == APlayer::round(this->_posX) && y == APlayer::round(this->_posY)))
    {
      this->_goTo = NO_DIRECTION;
      return ;
    }
  while (mapOfLee[POS_TAB(x, y, this->_map->getSizeX())] > 1)
    {
      value = mapOfLee[POS_TAB(x, y, this->_map->getSizeX())];
      if (x + 1 < static_cast<int>(this->_map->getSizeX()) && mapOfLee[POS_TAB(x + 1, y, this->_map->getSizeX())] == value - 1)
	++x;
      else if (y + 1 < static_cast<int>(this->_map->getSizeX()) && mapOfLee[POS_TAB(x, y + 1, this->_map->getSizeX())] == value - 1)
	++y;
      else if (x - 1 >= 0 && mapOfLee[POS_TAB(x - 1, y, this->_map->getSizeX())] == value - 1)
	--x;
      else if (y - 1 >= 0 && mapOfLee[POS_TAB(x, y - 1, this->_map->getSizeX())] == value - 1)
	--y;
      else
	{
	  this->_goTo = NO_DIRECTION;
	  return ;
	}
    }
  if (x + 1 < static_cast<int>(this->_map->getSizeX()) && mapOfLee[POS_TAB(x + 1, y, this->_map->getSizeX())] == INT_POS_IA)
    this->_goTo = LEFT;
  else if (y + 1 < static_cast<int>(this->_map->getSizeX()) && mapOfLee[POS_TAB(x, y + 1, this->_map->getSizeX())] == INT_POS_IA)
    this->_goTo = UP;
  else if (x - 1 >= 0 && mapOfLee[POS_TAB(x - 1, y, this->_map->getSizeX())] == INT_POS_IA)
    this->_goTo = RIGHT;
  else if (y - 1 >= 0 && mapOfLee[POS_TAB(x, y - 1, this->_map->getSizeX())] == INT_POS_IA)
    this->_goTo = DOWN;
  else
    this->_goTo = NO_DIRECTION;
}

bool				IA::isEnnemyAround(std::vector<int> &mapOfInt) const
{
  int				x = APlayer::round(this->_posX);
  int				y = APlayer::round(this->_posY);

  for (int count = 0; static_cast<unsigned int>(count) <= this->_rangeBomb; ++count)
    {
      if (x + count >= static_cast<int>(this->_map->getSizeX()) ||
	  (mapOfInt[POS_TAB(x + count, y, this->_map->getSizeX())] < 0 &&
	   mapOfInt[POS_TAB(x + count, y, this->_map->getSizeX())] != INT_DEFAULT &&
	   mapOfInt[POS_TAB(x + count, y, this->_map->getSizeX())] != INT_FIRE))
	break;
      if (mapOfInt[POS_TAB(x + count, y, this->_map->getSizeX())] == INT_PLAYER)
	return (true);
    }

  for (int count = 1; static_cast<unsigned int>(count) <= this->_rangeBomb; ++count)
    {
      if (x - count < 0 ||
	  (mapOfInt[POS_TAB(x - count, y, this->_map->getSizeX())] < 0 &&
	   mapOfInt[POS_TAB(x - count, y, this->_map->getSizeX())] != INT_DEFAULT &&
	   mapOfInt[POS_TAB(x - count, y, this->_map->getSizeX())] != INT_FIRE))
	break;
      if (mapOfInt[POS_TAB(x - count, y, this->_map->getSizeX())] == INT_PLAYER)
	return (true);
    }

  for (int count = 1; static_cast<unsigned int>(count) <= this->_rangeBomb; ++count)
    {
      if (y + count >= static_cast<int>(this->_map->getSizeY()) ||
	  (mapOfInt[POS_TAB(x, y + count, this->_map->getSizeX())] < 0 &&
	   mapOfInt[POS_TAB(x, y + count, this->_map->getSizeX())] != INT_DEFAULT &&
	   mapOfInt[POS_TAB(x, y + count, this->_map->getSizeX())] != INT_FIRE))
	break;
      if (mapOfInt[POS_TAB(x, y + count, this->_map->getSizeX())] == INT_PLAYER)
	return (true);
    }

  for (int count = 1; static_cast<unsigned int>(count) <= this->_rangeBomb; ++count)
    {
      if (y - count < 0 ||
	  (mapOfInt[POS_TAB(x, y - count, this->_map->getSizeX())] < 0 &&
	   mapOfInt[POS_TAB(x, y - count, this->_map->getSizeX())] != INT_DEFAULT &&
	   mapOfInt[POS_TAB(x, y - count, this->_map->getSizeX())] != INT_FIRE))
	break;
      if (mapOfInt[POS_TAB(x, y - count, this->_map->getSizeX())] == INT_PLAYER)
	return (true);
    }
  return (false);
}

bool				IA::findBonus(std::vector<int> &mapOfInt, std::vector<int> &mapOfLee)
{
  int				closest = -1;

  for (unsigned int count = 0; count < mapOfLee.size(); ++count)
    {
      if (mapOfLee[count] >= 0
	  && (mapOfLee[count] < closest || closest == -1)
	  && mapOfInt[count] == INT_BONUS)
	{
	  closest = mapOfLee[count];
	  this->_goToX = count % this->_map->getSizeX();
	  this->_goToY = count / this->_map->getSizeX();
	}
    }
  if (closest == -1)
    return (false);
  return (true);
}

bool				IA::findWall(std::vector<int> &mapOfInt, std::vector<int> &mapOfLee)
{
  int				closest = -1;

  for (unsigned int count = 0; count < mapOfLee.size(); ++count)
    {
      if (mapOfInt[count] == INT_WALLD)
	{
	  if (count % this->_map->getSizeX() + 1 < this->_map->getSizeX() &&
	      mapOfLee[count + 1] >= 0
	      && (mapOfLee[count + 1] < closest || closest == -1))
	    {
	      closest = mapOfLee[count + 1];
	      this->_goToX = count % this->_map->getSizeX() + 1;
	      this->_goToY = count / this->_map->getSizeX();
	    }

	  if (static_cast<int>(count % this->_map->getSizeX() - 1) >= 0 &&
	      mapOfLee[count - 1] >= 0
	      && (mapOfLee[count - 1] < closest || closest == -1))
	    {
	      closest = mapOfLee[count - 1];
	      this->_goToX = count % this->_map->getSizeX() - 1;
	      this->_goToY = count / this->_map->getSizeX();
	    }

	  if (count / this->_map->getSizeX() + 1 < this->_map->getSizeY() &&
	      mapOfLee[count + this->_map->getSizeX()] >= 0
	      && (mapOfLee[count + this->_map->getSizeX()] < closest || closest == -1))
	    {
	      closest = mapOfLee[count + this->_map->getSizeX()];
	      this->_goToX = count % this->_map->getSizeX();
	      this->_goToY = count / this->_map->getSizeX() + 1;
	    }

	  if (static_cast<int>(count / this->_map->getSizeX() - 1) >= 0 &&
	      mapOfLee[count - this->_map->getSizeX()] >= 0
	      && (mapOfLee[count - this->_map->getSizeX()] < closest || closest == -1))
	    {
	      closest = mapOfLee[count - this->_map->getSizeX()];
	      this->_goToX = count % this->_map->getSizeX();
	      this->_goToY = count / this->_map->getSizeX() - 1;
	    }
	}
    }

  if (closest == -1)
    return (false);
  _forceBomb = true;
  return (true);
}

bool				IA::findEnnemy(std::vector<int> &mapOfInt, std::vector<int> &mapOfLee)
{
  int				closest = -1;

  for (unsigned int count = 0; count < mapOfLee.size(); ++count)
    {
      if (mapOfLee[count] >= 0
	  && (mapOfLee[count] < closest || closest == -1)
	  && mapOfInt[count] == INT_PLAYER)
	{
	  closest = mapOfLee[count];
	  this->_goToX = count % this->_map->getSizeX();
	  this->_goToY = count / this->_map->getSizeX();
	}
    }
  if (closest == -1)
    return (false);
  return (true);
}
