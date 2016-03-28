//
// OpenDir.cpp for OpenDir.cpp in /home/abgral_f/rendu/cpp_bomberman/src/Game
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon May 26 14:07:31 2014 abgral_f
// Last update Mon May 26 15:17:51 2014 abgral_f
//

#include			"Game/ListFiles.hh"

ListFiles::ListFiles() {}

ListFiles::~ListFiles() {}

std::vector<std::string>	ListFiles::openDir(const char *path, std::vector<std::string>  &_filesList)
{
  DIR					*dirFlux;
  struct dirent				*file;

  if ((dirFlux = opendir(path)) == NULL)
    throw std::runtime_error("openDir Error: Directory does not exist");
  while ((file = readdir(dirFlux)) != NULL)
    if (file->d_name[0] != '.')
      _filesList.push_back(/*new std::string(*/file->d_name/*)*/);
  return (_filesList);
}
