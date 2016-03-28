//
// GetGDL.cpp for GetGDL.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Wed Jun  4 16:57:35 2014 LOEB Thomas
// Last update Wed Jun  4 17:19:34 2014 LOEB Thomas
//

#include	"GUI/GetGDL.hh"

GetGDL::GetGDL() : SdlContext() {}

GetGDL::~GetGDL() {}

SDL_Window *GetGDL::getWindow() const {
  return (_window);
}
