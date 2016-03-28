//
// Mutex.cpp for Mutex.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Fri May  9 13:59:50 2014 CHAUCHET Alan
// Last update Thu May 22 15:41:29 2014 CHAUCHET Alan
//

#include		"Thread/Mutex.hh"

Mutex::Mutex(void)
{
}

Mutex::~Mutex()
{
}

void			Mutex::create(void)
{
  int			err;

  if ((err = pthread_mutex_init(&(this->_mutex), NULL)))
    {
      std::string	errMsg(strerror(err));
      throw MutexError("function create : " + errMsg);
    }
}

void			Mutex::destroy(void)
{
  int			err;

  if ((err = pthread_mutex_destroy(&(this->_mutex))))
    {
      std::string	errMsg(strerror(err));
      throw MutexError("function destroy : " + errMsg);
    }
}

void			Mutex::lock(void)
{
  int			err;

  if ((err = pthread_mutex_lock(&(this->_mutex))))
    {
      std::string	errMsg(strerror(err));
      throw MutexError("function lock : " + errMsg);
    }
}

int			Mutex::trylock(void)
{
  int			err;

  if ((err = pthread_mutex_lock(&(this->_mutex))) != 0 && err != EBUSY)
    {
      std::string	errMsg(strerror(err));
      throw MutexError("function trylock : " + errMsg);
    }
  return (err);
}

void			Mutex::unlock(void)
{
  int			err;

  if ((err = pthread_mutex_unlock(&(this->_mutex))))
    {
      std::string	errMsg(strerror(err));
      throw MutexError("function unlock : " + errMsg);
    }
}

MutexError::MutexError(const std::string &msg) : std::runtime_error(msg)
{
  std::ostringstream    oss;

  oss << "MUTEX ERROR: " << msg;
  this->_msg = oss.str();
}

MutexError::~MutexError() throw() {}

const char                      *MutexError::what() const throw()
{
  return (this->_msg.c_str());
}
