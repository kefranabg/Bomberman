//
// NormalButton.cpp for NormalButton.cpp in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 15:13:30 2014 abgral_f
// Last update Fri May 23 14:32:32 2014 abgral_f
//

#include		"Menu/NormalButton.hh"

NormalButton::NormalButton(float posX, float posY,
			   float sizeX, float sizeY,
			   fctPtr method, const std::string &name,
			   Menu *menu)
  : AButton(posX, posY, sizeX, sizeY, method, menu),
    _name(name)
{
  this->_type = Normal;
  this->_isSelect = false;
  this->_textCursorY = posY - sizeY / 6;
  this->_geometryButton = new gdl::Geometry();
  this->_geometryLetters = new gdl::Geometry();
}

NormalButton::~NormalButton() {}

void			NormalButton::buildNewGeo()
{
  float                 z = 0;

  if (!this->_geometryButton)
    delete this->_geometryButton;
  if (!this->_geometryLetters)
    delete this->_geometryLetters;
  this->_geometryButton = new gdl::Geometry();
  this->_geometryLetters = new gdl::Geometry();
  if (this->_isSelect == true)
    z = 5;
  _geometryButton->pushVertex(glm::vec3(_posX, _posY, z));
  _geometryButton->pushVertex(glm::vec3(_posX + _sizeX, _posY, z));
  _geometryButton->pushVertex(glm::vec3(_posX + _sizeX, _posY - _sizeY, z));
  _geometryButton->pushVertex(glm::vec3(_posX, _posY - _sizeY, z));
  _geometryButton->pushUv(glm::vec2(0.0, 0.0));
  _geometryButton->pushUv(glm::vec2(1, 0.0));
  _geometryButton->pushUv(glm::vec2(1, 1));
  _geometryButton->pushUv(glm::vec2(0.0, 1));
  this->displayText(z, this->_name);
  _geometryButton->build();
  _geometryLetters->build();
}
