//
// Mutex.hh for Mutex.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May  7 17:20:45 2014 CHAUCHET Alan
// Last update Thu May 22 15:42:05 2014 CHAUCHET Alan
//

#ifndef			MUTEX_HH_
# define		MUTEX_HH_

# include		<pthread.h>
# include		<errno.h>
# include		<string.h>
# include               <string>
# include               <stdexcept>
# include               <sstream>

class			Mutex
{
  pthread_mutex_t	_mutex;

public:
  Mutex(void);
  ~Mutex();
  void			create(void);
  void			destroy(void);
  void			lock(void);
  int			trylock(void);
  void			unlock(void);
};

class                   MutexError : public std::runtime_error
{
  std::string           _msg;

public:
  MutexError(const std::string &);
  virtual ~MutexError() throw();
  virtual const char    *what() const throw();
};

#endif
