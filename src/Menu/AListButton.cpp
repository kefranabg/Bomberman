//
// AListButton.cpp for AListButton.cpp in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 16:40:31 2014 abgral_f
// Last update Sat May 24 16:37:04 2014 abgral_f
//

#include		"Menu/AListButton.hh"

AListButton::AListButton(float posX, float posY,
			 float sizeX, float sizeY,
			 fctPtr method, Menu *menu)
  : AButton(posX, posY, sizeX, sizeY, method, menu)
{
  this->_displayRight = true;
  this->_displayLeft = false;
  this->_moovArrowLeft = 0;
  this->_moovArrowRight = 0;
}

AListButton::~AListButton() {}

gdl::Geometry             *AListButton::getGeometryLeftArrow() const
{
  return (this->_geometryLeftArrow);
}

gdl::Geometry             *AListButton::getGeometryRightArrow() const
{
  return (this->_geometryRightArrow);
}

bool			  AListButton::getDisplayRight() const
{
  return (this->_displayRight);
}

bool			  AListButton::getDisplayLeft() const
{
  return (this->_displayLeft);
}
