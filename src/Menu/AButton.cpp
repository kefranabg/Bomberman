//
// AButton.cpp for AButton.cpp in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 13:53:17 2014 abgral_f
// Last update Mon May 26 15:54:45 2014 abgral_f
//

#include		"Menu/AButton.hh"

AButton::AButton(float posX, float posY,
		 float sizeX, float sizeY,
		 fctPtr method, Menu *menu)
  : _posX(posX), _posY(posY),
    _sizeX(sizeX), _sizeY(sizeY),
    _method(method), _menu(menu)
{
  this->_isSelect = false;
  this->_textCursorY = posY - sizeY / 6;
}

AButton::~AButton() {}

AButton::fctPtr            AButton::getMethod() const
{
  return (this->_method);
}

AButton::buttonType        AButton::getType() const
{
  return (this->_type);
}

bool                      AButton::getIsSelect() const
{
  return (this->_isSelect);
}

gdl::Geometry             *AButton::getGeometryButton() const
{
  return (this->_geometryButton);
}

void                      AButton::setIsSelect(bool isSelect)
{
  this->_isSelect = isSelect;
}

gdl::Geometry             *AButton::getGeometryLetters() const
{
  return (this->_geometryLetters);
}

void                      AButton::moovTextCursor(float x, float y)
{
  this->_textCursorX += x;
  this->_textCursorY += y;
}

bool                      AButton::getC(char charac, std::vector<glm::vec2 *> &list)
{
  std::string		alphabet("abcdefghijklmnopqrstuvwxyz1234567890 ");
  unsigned int		count = 0;
  double		x, y;

  while (alphabet[count] != charac
         && count != alphabet.size())
    count++;
  if (count == alphabet.size())
    count -= 1;
  x = count % 6;
  y = (count / 6) + 1;
  x *= 0.166666666667;
  y *= 0.142857142857;
  list.push_back(new glm::vec2(x, 1 - y ));
  list.push_back(new glm::vec2(x + 0.166666666667, 1 - y));
  list.push_back(new glm::vec2(x + 0.166666666667, 1 - y + 0.142857142857));
  list.push_back(new glm::vec2(x,  1 - y + 0.142857142857));
  return (true);
}

void                    AButton::displayText(float z, const std::string &text)
{
  this->_textCursorX = _posX + (_sizeX / 2) - (_sizeY / 6) * 4 * 0.8 / 2 * text.size();
  float oldX = _textCursorX, oldY = _textCursorY;

  for (unsigned int i = 0 ; i != text.size() ; i++)
    {
      std::vector<glm::vec2 *> list;
      this->getC(text[i], list);
      _geometryLetters->pushVertex(glm::vec3(_textCursorX, _textCursorY, 1 + z));
      _geometryLetters->pushVertex(glm::vec3(_textCursorX + (_sizeY / 6) * 4, _textCursorY, 1 + z));
      _geometryLetters->pushVertex(glm::vec3(_textCursorX + (_sizeY / 6) * 4,
                                             _textCursorY - (_sizeY / 6) * 4, 1 + z));
      _geometryLetters->pushVertex(glm::vec3(_textCursorX, _textCursorY - (_sizeY / 6) * 4, 1 + z));
      _geometryLetters->pushUv(*(list[3]));
      _geometryLetters->pushUv(*(list[2]));
      _geometryLetters->pushUv(*(list[1]));
      _geometryLetters->pushUv(*(list[0]));
      this->moovTextCursor((_sizeY / 6) * 4 * 0.8, 0);
    }
  this->_textCursorX = oldX;
  this->_textCursorY = oldY;
}
