//
// Cond.cpp for Cond.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Fri May  9 14:49:45 2014 CHAUCHET Alan
// Last update Sun May 11 11:16:29 2014 CHAUCHET Alan
//

#include		"Thread/Cond.hh"

void			Cond::create(void)
{
  int			err;

  if ((err = pthread_cond_init(&(this->_condVar), NULL)) ||
      (err = pthread_mutex_init(&(this->_mutex), NULL)))
    {
      std::string	errMsg(strerror(err));
      throw CondError("function create : " + errMsg);
    }
}

void			Cond::destroy(void)
{
  int			err;

  if ((err = pthread_cond_destroy(&(this->_condVar))) ||
      (err = pthread_mutex_destroy(&(this->_mutex))))
    {
      std::string	errMsg(strerror(err));
      throw CondError("function destroy : " + errMsg);
    }
}

void			Cond::wait(void)
{
  int			err;

  if ((err = pthread_mutex_lock(&(this->_mutex))) ||
      (err = pthread_cond_wait(&(this->_condVar), &(this->_mutex))) ||
      (err = pthread_mutex_unlock(&(this->_mutex))))
    {
      std::string	errMsg(strerror(err));
      throw CondError("function wait : " + errMsg);
    }
}

int			Cond::timedwait(long tv_sec, long tv_nsec)
{
  int			err;
  int                   ret;
  struct timeval        now;
  struct timespec       param;

  gettimeofday(&now, NULL);
  param.tv_sec = now.tv_sec + tv_sec + (((now.tv_usec * 1000) + tv_nsec) / 1000000000);
  param.tv_nsec = ((now.tv_usec * 1000) + tv_nsec) % 1000000000;
  if ((err = pthread_mutex_lock(&(this->_mutex))))
    {
      std::string	errMsg(strerror(err));
      throw CondError("function timedwait : " + errMsg);
    }
  ret = pthread_cond_timedwait(&(this->_condVar), &(this->_mutex), &param);
  if ((err = pthread_mutex_unlock(&(this->_mutex))))
    {
      std::string	errMsg(strerror(err));
      throw CondError("function timedwait : " + errMsg);
    }
  return (ret);
}

int			Cond::timedwait(const struct timespec *param)
{
  int			err;
  int                   ret;

  if ((err = pthread_mutex_lock(&(this->_mutex))))
    {
      std::string	errMsg(strerror(err));
      throw CondError("function timedwait : " + errMsg);
    }
  ret = pthread_cond_timedwait(&(this->_condVar), &(this->_mutex), param);
  if ((err = pthread_mutex_unlock(&(this->_mutex))))
    {
      std::string	errMsg(strerror(err));
      throw CondError("function timedwait : " + errMsg);
    }
  return (ret);
}

void			Cond::signal(void)
{
  int			err;

  if ((err = pthread_cond_signal(&(this->_condVar))))
    {
      std::string	errMsg(strerror(err));
      throw CondError("function signal : " + errMsg);
    }
}

void			Cond::broadcast(void)
{
  int			err;

  if ((err = pthread_cond_broadcast(&(this->_condVar))))
    {
      std::string	errMsg(strerror(err));
      throw CondError("function broadcast : " + errMsg);
    }
}

CondError::CondError(const std::string &msg) : std::runtime_error(msg)
{
  std::ostringstream    oss;

  oss << "COND ERROR: " << msg;
  this->_msg = oss.str();
}

CondError::~CondError() throw() {}

const char                      *CondError::what() const throw()
{
  return (this->_msg.c_str());
}
