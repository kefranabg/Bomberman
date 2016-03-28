//
// Text.hh for Text.hh in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Tue May 20 12:32:27 2014 abgral_f
// Last update Thu Jun 12 13:12:12 2014 abgral_f
//

#ifndef                 TEXT_HH_
# define                TEXT_HH_

#include                <Geometry.hh>
#include                <glm/glm.hpp>
#include                <vector>

class			Text
{
public:
  Text(float, float, float, float, const std::string &, bool error = false);
  ~Text();
  void                      moovTextCursor(float, float);
  void			    buildText();
  gdl::Geometry             *getGeometryText() const;
  void			    setDisplay(double);
  void			    setIsCentered(bool);
private:
  bool			  _isCentered;
  float                   _textCursorX;
  float                   _textCursorY;
  float                   _posX;
  float			  _posY;
  float			  _sizeX;
  float			  _sizeY;
  gdl::Geometry           *_geometry;
  std::string		  _text;
  bool			  _error;
  double		  _display;
};

#endif
