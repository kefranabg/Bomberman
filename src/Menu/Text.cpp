//
// Text.cpp for Text.cpp in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Tue May 20 12:36:55 2014 abgral_f
// Last update Thu Jun 12 13:35:32 2014 abgral_f
//

#include		"Menu/Text.hh"
#include		"Menu/AButton.hh"

Text::Text(float textCursorX, float textCursorY, float sizeX, float sizeY, const std::string &text
	   , bool error)
  : _textCursorX(textCursorX), _textCursorY(textCursorY),
    _sizeX(sizeX), _sizeY(sizeY), _text(text), _error(error)
{
  this->_posX = textCursorX;
  this->_posY = textCursorY;
  this->_isCentered = false;
  this->_geometry = new gdl::Geometry();
  this->_display = 1;
}


Text::~Text()
{

}

void                      Text::moovTextCursor(float x, float y)
{
  this->_textCursorX += x;
  this->_textCursorY += y;
}

gdl::Geometry             *Text::getGeometryText() const
{
  return (this->_geometry);
}

void                      Text::buildText()
{
  if (_error == true)
    _geometry->setColor(glm::vec4(1, 0, 0, this->_display));
  if (_isCentered == false)
    {
      for (unsigned int i = 0 ; i != _text.size() ; i++)
	{
	  std::vector<glm::vec2 *> list;
	  if (AButton::getC(_text[i], list) == false)
	    return ;
	  _geometry->pushVertex(glm::vec3(_textCursorX, _textCursorY, 1));
	  _geometry->pushVertex(glm::vec3(_textCursorX + _sizeX, _textCursorY, 1));
	  _geometry->pushVertex(glm::vec3(_textCursorX + _sizeX, _textCursorY - _sizeY, 1));
	  _geometry->pushVertex(glm::vec3(_textCursorX, _textCursorY - _sizeY, 1));
	  _geometry->pushUv(*(list[3]));
	  _geometry->pushUv(*(list[2]));
	  _geometry->pushUv(*(list[1]));
	  _geometry->pushUv(*(list[0]));
	  this->moovTextCursor(_sizeX * 0.8, 0);
	}
    }
  else
    {
      this->_textCursorX = _posX + (_sizeX / 2) - (_sizeY / 6) * 4 * 0.8 / 2 * _text.size();
      float oldX = _textCursorX, oldY = _textCursorY;

      for (unsigned int i = 0 ; i != _text.size() ; i++)
	{
	  std::vector<glm::vec2 *> list;
	  if (AButton::getC(_text[i], list) == false)
	    return ;
	  _geometry->pushVertex(glm::vec3(_textCursorX, _textCursorY, 5));
	  _geometry->pushVertex(glm::vec3(_textCursorX + (_sizeY / 6) * 4, _textCursorY, 5));
	  _geometry->pushVertex(glm::vec3(_textCursorX + (_sizeY / 6) * 4,
						 _textCursorY - (_sizeY / 6) * 4, 5));
	  _geometry->pushVertex(glm::vec3(_textCursorX, _textCursorY - (_sizeY / 6) * 4, 5));
	  _geometry->pushUv(*(list[3]));
	  _geometry->pushUv(*(list[2]));
	  _geometry->pushUv(*(list[1]));
	  _geometry->pushUv(*(list[0]));
	  this->moovTextCursor((_sizeY / 6) * 4 * 0.8, 0);
	}
      this->_textCursorX = oldX;
      this->_textCursorY = oldY;
    }
  this->_geometry->build();
}

void			Text::setIsCentered(bool value)
{
  this->_isCentered = value;
}
