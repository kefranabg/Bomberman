//
// Rand.hh for Rand.hh in /home/acca_b/rendu/cpp_bomberman
//
// Made by Baptiste Acca
// Login   <acca_b@epitech.net>
//
// Started on  Tue May 13 15:34:02 2014 Baptiste Acca
// Last update Tue May 13 15:59:25 2014 Baptiste Acca
//

#ifndef RAND_HH_
# define RAND_HH_

# include <cstdlib>
# include <ctime>

class Rand {
public:
  Rand(void);
  ~Rand(void);
  unsigned int rand(unsigned int const, unsigned int const) const;
};

#endif
