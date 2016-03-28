//
// Thread.cpp for Thread.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Fri May  9 13:37:43 2014 CHAUCHET Alan
// Last update Mon May 26 12:46:17 2014 CHAUCHET Alan
//

#include		"Thread/Thread.hh"

void			Thread::create(threadFunction callFunction, void *param)
{
  if (pthread_create(&(this->_thread), NULL, callFunction, param))
    throw ThreadError("cannot create a new thread.");
}

void			Thread::cancel(void)
{
  pthread_cancel(this->_thread);
}

void			*Thread::wait(void)
{
  void			*ret;

  if (pthread_join(this->_thread, &ret) == EDEADLK)
    this->cancel();
  return (ret);
}

void			Thread::exit(void *ret)
{
  pthread_exit(ret);
}

ThreadError::ThreadError(const std::string &msg) : std::runtime_error(msg)
{
  std::ostringstream    oss;

  oss << "THREAD ERROR: " << msg;
  this->_msg = oss.str();
}

ThreadError::~ThreadError() throw() {}

const char                      *ThreadError::what() const throw()
{
  return (this->_msg.c_str());
}
