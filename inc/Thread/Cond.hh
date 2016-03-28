//
// Cond.hh for Cond.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May  7 17:20:45 2014 CHAUCHET Alan
// Last update Fri May  9 15:04:33 2014 CHAUCHET Alan
//

#ifndef			COND_HH_
# define		COND_HH_

# include		<pthread.h>
# include		<errno.h>
# include		<string.h>
# include		<sys/time.h>
# include               <string>
# include               <stdexcept>
# include               <sstream>

class			Cond
{
  pthread_cond_t	_condVar;
  pthread_mutex_t	_mutex;

public:
  void			create(void);
  void			destroy(void);
  void			wait(void);
  int			timedwait(long, long);
  int			timedwait(const struct timespec *);
  void			signal(void);
  void			broadcast(void);
};

class                   CondError : public std::runtime_error
{
  std::string           _msg;

public:
  CondError(const std::string &);
  virtual ~CondError() throw();
  virtual const char    *what() const throw();
};

#endif
