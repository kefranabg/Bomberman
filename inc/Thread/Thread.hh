//
// Thread.hh for Thread.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May  7 17:20:45 2014 CHAUCHET Alan
// Last update Mon May 26 12:44:47 2014 CHAUCHET Alan
//

#ifndef			THREAD_HH_
# define		THREAD_HH_

# include		<pthread.h>
# include		<errno.h>
# include		<string.h>
# include               <string>
# include               <stdexcept>
# include               <sstream>

typedef void		*(*threadFunction)(void *);

class			Thread
{
  pthread_t		_thread;

public:
  void			create(threadFunction, void *);
  void			cancel(void);
  void			*wait(void);
  void			exit(void *);
};

class                   ThreadError : public std::runtime_error
{
  std::string           _msg;

public:
  ThreadError(const std::string &);
  virtual ~ThreadError() throw();
  virtual const char    *what() const throw();
};

#endif
