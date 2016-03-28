//
// Bomb.cpp for Bomb.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Mon Jun  2 14:40:32 2014 CHAUCHET Alan
// Last update Sat Jun  7 15:30:52 2014 CHAUCHET Alan
//

#include		"Game/Bomb.hh"
#include		"GUI/Sound.hh"
#include		"Game/APlayer.hh"

Bomb::Bomb(Map *map, Cond *cond, APlayer *player)
{
  this->_player = player;
  this->_map = map;
  this->_cond = cond;
  this->_mutex.create();
  this->_isActiv = true;
  this->_posX = -1;
  this->_posY = -1;
  this->_range = 2;
  this->_timeToBomb = 3000000000;
  this->_pause = false;
  this->_stop = false;
}

Bomb::~Bomb()
{
  if (!this->_isActiv)
    this->_thread.wait();
  this->_mutex.destroy();
}

void			Bomb::setRange(unsigned int range)
{
  this->_mutex.lock();
  this->_range = range;
  this->_mutex.unlock();
}

unsigned int		Bomb::getRange(void) const
{
  return (this->_range);
}

void			Bomb::setTimeToBomb(long newTime)
{
  this->_timeToBomb = newTime;
}

long			Bomb::getTimeToBomb(void) const
{
  return (this->_timeToBomb);
}

void			Bomb::put(void)
{
  bool			left = true;
  bool			right = true;
  bool			up = true;
  bool			down = true;
  long			timeToBomb = this->_timeToBomb;
  struct timeval        first;
  struct timeval        second;
  bool			destroy;

  this->_mutex.lock();
  unsigned int		range = this->_range;
  this->_mutex.unlock();

  if (this->_pause)
    this->_cond->wait();
  this->_map->addObj(this->_posX, this->_posY, BOMB, destroy);
  gettimeofday(&first, NULL);
  while (timeToBomb > 0 && this->_cond->timedwait(0, timeToBomb) != ETIMEDOUT &&
	 !this->_map->isFire(this->_posX, this->_posY))
    {
      if (this->_stop)
	this->_thread.exit(NULL);
      gettimeofday(&second, NULL);
      timeToBomb -= ((second.tv_sec * 1000000000 - first.tv_sec * 1000000000) +
		     (second.tv_usec * 1000 - first.tv_usec * 1000));
      first.tv_usec = second.tv_usec;
      if (this->_pause)
	this->_cond->wait();
    }
  if (this->_stop)
    this->_thread.exit(NULL);
  if (this->_pause)
    this->_cond->wait();
  Sound::playSound(SOUND_EXPLOSE);
  this->_map->takeObj(this->_posX, this->_posY, BOMB);
  this->_map->addObj(this->_posX, this->_posY, FIRE, destroy);
  for (unsigned int count = 1; count <= range; count++)
    {
      if (this->_pause)
	this->_cond->wait();
      if (right)
	{
	  right = this->_map->addObj(this->_posX + count, this->_posY, FIRE, destroy);
	  if (destroy)
	    this->_player->setScore(this->_player->getScore() + 10);
	}
      if (left)
	{
	  left = this->_map->addObj(this->_posX - count, this->_posY, FIRE, destroy);
	  if (destroy)
	    this->_player->setScore(this->_player->getScore() + 10);
	}
      if (up)
	{
	  up = this->_map->addObj(this->_posX, this->_posY + count, FIRE, destroy);
	  if (destroy)
	    this->_player->setScore(this->_player->getScore() + 10);
	}
      if (down)
	{
	  down = this->_map->addObj(this->_posX, this->_posY - count, FIRE, destroy);
	  if (destroy)
	    this->_player->setScore(this->_player->getScore() + 10);
	}
    }
  if (this->_stop)
    this->_thread.exit(NULL);
  if (this->_pause)
    this->_cond->wait();
  this->_cond->broadcast();
  timeToBomb = 1000000000;
  gettimeofday(&first, NULL);
  while (timeToBomb > 0 && this->_cond->timedwait(0, timeToBomb) != ETIMEDOUT)
    {
      if (this->_stop)
	this->_thread.exit(NULL);
      gettimeofday(&second, NULL);
      timeToBomb -= ((second.tv_sec * 1000000000 - first.tv_sec * 1000000000) +
		     (second.tv_usec * 1000 - first.tv_usec * 1000));
      first.tv_usec = second.tv_usec;
      if (this->_pause)
	this->_cond->wait();
    }
  this->_map->takeObj(this->_posX, this->_posY, FIRE);
  for (unsigned int count = 1; count <= range; count++)
    {
      if (this->_pause)
	this->_cond->wait();
      this->_map->takeObj(this->_posX + count, this->_posY, FIRE);
      this->_map->takeObj(this->_posX - count, this->_posY, FIRE);
      this->_map->takeObj(this->_posX, this->_posY + count, FIRE);
      this->_map->takeObj(this->_posX, this->_posY - count, FIRE);
    }
  if (this->_stop)
    this->_thread.exit(NULL);
  if (this->_pause)
    this->_cond->wait();
  this->_mutex.lock();
  this->_posX = -1;
  this->_posY = -1;
  this->_isActiv = true;
  this->_mutex.unlock();
  this->_thread.exit(NULL);
}

bool			Bomb::launch(int posX, int posY)
{
  this->_mutex.lock();
  if (!this->_isActiv)
    {
      this->_mutex.unlock();
      return (false);
    }
  this->_mutex.unlock();
  this->_posX = posX;
  this->_posY = posY;
  this->_mutex.lock();
  this->_isActiv = false;
  this->_mutex.unlock();
  this->_thread.create(&callPut, this);
  return (true);
}

void			*callPut(void *param)
{
  Bomb			*bomb = static_cast<Bomb *>(param);

  bomb->put();
  return (NULL);
}

void			Bomb::setPause(bool pause)
{
  this->_mutex.lock();
  this->_pause = pause;
  this->_mutex.unlock();
}

bool			Bomb::getPause(void) const
{
  return (this->_pause);
}

void			Bomb::pause(void)
{
  this->setPause(true);
  this->_cond->broadcast();
}

void			Bomb::unpause(void)
{
  this->setPause(false);
  this->_cond->broadcast();
}

void			Bomb::stop(void)
{
  this->_mutex.lock();
  this->_stop = true;
  this->_mutex.unlock();
  this->_cond->broadcast();
}

bool			Bomb::isActiv(void) const
{
  return (this->_isActiv);
}

void			Bomb::setMap(Map *map)
{
  this->_map = map;
}
