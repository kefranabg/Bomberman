//
// TextBoxButton.cpp for TextBoxButton.cpp in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 17:37:28 2014 abgral_f
// Last update Thu Jun 12 13:06:37 2014 abgral_f
//

#include		"Menu/TextBoxButton.hh"
#include		"Menu/Menu.hh"

TextBoxButton::TextBoxButton(float posX, float posY,
			     float sizeX, float sizeY,
			     fctPtr method, const std::string &name,
			     bool oneCharac, Menu *menu)
  : AButton(posX, posY, sizeX, sizeY, method, menu),
    _name(name), _oneCharac(oneCharac)
{
  this->_type = TextBox;
  this->_canBeModified = false;
  this->_color = false;
  this->_geometryButton = new gdl::Geometry();
  this->_geometryLetters = new gdl::Geometry();
}

TextBoxButton::~TextBoxButton() {}

void              TextBoxButton::buildNewGeo()
{
  float		  z = 0;

  if (!this->_geometryButton)
    delete this->_geometryButton;
  if (!this->_geometryLetters)
    delete this->_geometryLetters;
  this->_geometryButton = new gdl::Geometry();
  this->_geometryLetters = new gdl::Geometry();
  if (this->_isSelect == true)
    z = 5;
  if (this->_color == true)
    _geometryButton->setColor(glm::vec4(0, 0, 1, 1));
  _geometryButton->pushVertex(glm::vec3(_posX, _posY, z));
  _geometryButton->pushVertex(glm::vec3(_posX + _sizeX, _posY, z));
  _geometryButton->pushVertex(glm::vec3(_posX + _sizeX, _posY - _sizeY, z));
  _geometryButton->pushVertex(glm::vec3(_posX, _posY - _sizeY, z));
  _geometryButton->pushUv(glm::vec2(0.0, 0.0));
  _geometryButton->pushUv(glm::vec2(1, 0.0));
  _geometryButton->pushUv(glm::vec2(1, 1));
  _geometryButton->pushUv(glm::vec2(0.0, 1));
  if (this->_name.size() == 0)
    this->displayText(z, " ");
  else
    this->displayText(z, this->_name);
  _geometryButton->build();
  _geometryLetters->build();
}

void                      TextBoxButton::changeText(const std::string &name)
{
  if (this->_oneCharac == true)
    {
      if (this->_menu->isKeyAlreadyUsed(name) == false
	  || name == this->_name)
	{
	  this->_name = name;
	  this->_canBeModified = false;
	  this->_color = false;
	}
    }
  else
    {
      if (name[0] == '\b' && this->_name.size() != 0)
        this->_name.erase(this->_name.end() - 1);
      else if (name[0] != '\b' && this->_name.size() < 10)
        this->_name += name;
    }
  this->buildNewGeo();
}

void                      TextBoxButton::setCanBeModified(bool value)
{
  this->_canBeModified = value;
  if (value == true)
    {
      this->_color = true;
      this->buildNewGeo();
    }
}

bool                      TextBoxButton::getCanBeModified() const
{
  return (this->_canBeModified);
}

bool                      TextBoxButton::getOneCharac() const
{
  return (this->_oneCharac);
}

const std::string	&TextBoxButton::getName() const
{
  return (this->_name);
}
