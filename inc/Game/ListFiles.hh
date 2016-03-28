//
// OpenDir.hh for OpenDir.hh in /home/abgral_f/rendu/cpp_bomberman/inc/Game
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon May 26 14:05:10 2014 abgral_f
// Last update Mon May 26 15:18:00 2014 abgral_f
//

#ifndef                 LISTFILES_HH_
# define                LISTFILES_HH_

#include                <iostream>
#include                <string>
#include		<stdexcept>
#include                <vector>
#include		<sys/types.h>
#include		<dirent.h>
#include		<stdio.h>

class			ListFiles
{
public:
  ListFiles();
  ~ListFiles();
  static std::vector<std::string>   openDir(const char *, std::vector<std::string> &);
};

#endif
