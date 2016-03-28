//
// Rand.cpp for Rand.cpp in /home/acca_b/rendu/cpp_bomberman
//
// Made by Baptiste Acca
// Login   <acca_b@epitech.net>
//
// Started on  Tue May 13 15:33:29 2014 Baptiste Acca
// Last update Tue May 13 15:59:53 2014 Baptiste Acca
//

#include "Game/Rand.hh"

Rand::Rand(void)
{
  srand(time(NULL));
}

Rand::~Rand(void)
{

}

unsigned int Rand::rand(unsigned int const min, unsigned int const max) const
{
  return ((::rand() % (max - min)) + min);
}
