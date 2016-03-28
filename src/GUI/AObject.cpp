//
// AObject.cpp for AObject.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:14:46 2014 LOEB Thomas
// Last update Fri Jun 13 17:25:02 2014 Maxime Manzano
//

#include	<iostream>
#include	"GUI/AObject.hh"

AObject::AObject() : _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1), _coord(0, 0, 0), _idx(-1) {}

AObject::AObject(bool anim) : _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1), _coord(0, 0, 0), _idx(-1)
{
  _anim = anim;
}

AObject::~AObject() {}

void		AObject::setCurrentAnim(int idx, bool loop)
{
  if (idx != _idx)
    {
      _idx = idx;
      if (_idx < static_cast<int>(_animations.size()) && _idx >= 0)
	_model.setCurrentSubAnim(_animations[_idx], loop);
    }
}

int		AObject::getIdx() const
{
  return (this->_idx);
}

void		AObject::setIdx(int idx)
{
  _idx = idx;
}

void		AObject::translate(glm::vec3 const &transformation)
{
  _position += transformation;
}

void		AObject::rotate(glm::vec3 const& axis, float angle)
{
  _rotation += axis * angle;
}

glm::mat4	AObject::getTransformation() {
  glm::mat4 transform(1);

  transform = glm::translate(transform, _position);
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::scale(transform, _scale);
  return (transform);
}

glm::vec3	AObject::getPosition() const {
  return (this->_position);
}

glm::vec3	AObject::getRotation() const {
  return (this->_rotation);
}

glm::vec3	AObject::getScale() const {
  return (this->_scale);
}

glm::vec3	AObject::getCoord() const {
  return (this->_coord);
}

void		AObject::setCoord(glm::vec3 const &coord) {
  this->_coord = coord;
}

void		AObject::setScale(glm::vec3 const &scale) {
  this->_scale = scale;
}

void		AObject::setRotation(glm::vec3 const &rotation) {
  this->_rotation = rotation;
}
