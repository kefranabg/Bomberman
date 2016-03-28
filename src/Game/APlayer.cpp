//
// APlayer.cpp for APlayer.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Mon Jun  2 14:40:44 2014 CHAUCHET Alan
// Last update Fri Jun 13 18:18:28 2014 LOEB Thomas
//

#include	"Game/APlayer.hh"
#include	"Game/BomberGame.hh"
#include	"GUI/MapGUI.hh"
#include	"GUI/PlayerGUI.hh"
#include	"GUI/Sound.hh"

APlayer::APlayer(BomberGame *game, e_playerType type, double posX, double posY) :  _isAlive(true), _type(type), _speed(0.05), _posX(posX), _posY(posY), _score(0)
{
  this->_map = game->getMap();
  this->_cond = game->getCondBomb();
  this->addBomb();
  this->incrMove[0][0] = 0;
  this->incrMove[0][1] = 0;
  this->incrMove[0][2] = -1;
  this->incrMove[0][3] = 1;
  this->incrMove[1][0] = -1;
  this->incrMove[1][1] = 1;
  this->incrMove[1][2] = 0;
  this->incrMove[1][3] = 0;
  this->_rangeBomb = 2;
  this->_takeBonus[0] = &APlayer::addBomb;
  this->_takeBonus[1] = &APlayer::increaseBombRange;
  this->_takeBonus[2] = &APlayer::increaseSpeed;
  this->_scoreMutex.create();
}

APlayer::~APlayer()
{
  this->_isAlive = false;
  this->_thread.wait();
  this->killBombs();
}

void		APlayer::killBombs(void)
{
  for (unsigned int count = 0; count < this->_bombs.size(); ++count)
    {
      this->_bombs[count]->stop();
      delete(this->_bombs[count]);
    }
  this->_bombs.clear();
}

int		APlayer::round(double d)
{
  int ret = d;

  if (d - ret >= 0.5)
    ++ret;
  return (ret);
}

void		APlayer::addBomb(void)
{
  this->_bombs.push_back(new Bomb(this->_map, this->_cond, this));
}

void		APlayer::increaseBombRange(void)
{
  for (unsigned int i = 0; i < this->_bombs.size(); ++i)
    this->_bombs[i]->setRange(this->_bombs[i]->getRange() + 1);
  ++this->_rangeBomb;
}

void		APlayer::increaseSpeed(void)
{
  this->_speed += 0.01;
  if (this->_speed > 0.08)
    this->_speed = 0.08;
}

void		APlayer::putBomb(void)
{
  int x = APlayer::round(this->_posX), y = APlayer::round(this->_posY);

  for (unsigned int i = 0; i < this->_bombs.size(); ++i)
    if (this->_bombs[i]->launch(x, y))
      {
	Sound::playSound(SOUND_PUT_BOMB);
	return ;
      }
}

void		APlayer::move(e_direction d)
{
  int x = APlayer::round(this->_posX + this->_speed * this->incrMove[0][d] + this->incrMove[0][d] * 0.2),
    y = APlayer::round(this->_posY + this->_speed * this->incrMove[1][d] + this->incrMove[1][d] * 0.2);

  if (x < 0 || y < 0 ||
      (this->_map->isObstacle(x, y) == true &&
       (APlayer::round(this->_posX) != x || APlayer::round(this->_posY) != y)))
    return ;
  this->_posX += this->_speed * this->incrMove[0][d];
  this->_posY += this->_speed * this->incrMove[1][d];
}

void		APlayer::die(void)
{
  this->_isAlive = false;
}

e_playerType	APlayer::getType(void) const
{
  return (this->_type);
}

bool		APlayer::isAlive(void) const
{
  return (this->_isAlive);
}

void		APlayer::launch(void)
{
  this->_thread.create(&launchPlayer, this);
}

void		*launchPlayer(void *player)
{
  APlayer *ap = static_cast<APlayer *>(player);

  ap->play();
  return (NULL);
}

void		APlayer::checkMap(void)
{
  int x = APlayer::round(this->_posX), y = APlayer::round(this->_posY);

  if (this->_map->isFire(x, y))
    {
      Sound::playSound(SOUND_DIE);
      this->_isAlive = false;
    }
  else if (this->_map->isBonus(x, y))
    {
      e_typeObj		bonus;

      if (this->_map->takeBonus(x, y, bonus))
	{
	  this->setScore(this->_score + 30);
	  (this->*(this->_takeBonus[static_cast<int>(bonus) - 2]))();
	  Sound::playSound(SOUND_BONUS);
	}
    }
}

double		APlayer::getPosX(void) const
{
  return (this->_posX);
}

double		APlayer::getPosY(void) const
{
  return (this->_posY);
}

void		APlayer::setRangeBomb(unsigned int range)
{
  this->_rangeBomb = range;
  for (unsigned int count = 0; count < this->_bombs.size(); count++)
    this->_bombs[count]->setRange(range);
}

unsigned int	APlayer::getRangeBomb(void) const
{
  return (this->_rangeBomb);
}

void		APlayer::setSpeed(double speed)
{
  this->_speed = speed;
}

double		APlayer::getSpeed(void) const
{
  return (this->_speed);
}

void		APlayer::setScore(unsigned int score)
{
  this->_scoreMutex.lock();
  this->_score = score;
  this->_scoreMutex.unlock();
}

unsigned int	APlayer::getScore(void) const
{
  return (this->_score);
}

unsigned int	APlayer::getNbBombs(void) const
{
  return (this->_bombs.size());
}

unsigned int	APlayer::getNbBombsAvailable(void) const
{
  unsigned int	nbBombs = 0;

  for (unsigned int count = 0; count < this->_bombs.size(); count++)
    if (this->_bombs[count]->isActiv())
      nbBombs++;
  return (nbBombs);
}

void		APlayer::pauseBombs(void) const
{
  for (unsigned int count = 0; count < this->_bombs.size(); count++)
    this->_bombs[count]->pause();
}

void		APlayer::unpauseBombs(void) const
{
  for (unsigned int count = 0; count < this->_bombs.size(); count++)
    this->_bombs[count]->unpause();
}

void		APlayer::setMap(Map *map)
{
  this->_map = map;
  for (unsigned int count = 0; count < this->_bombs.size(); ++count)
    this->_bombs[count]->setMap(this->_map);
}
