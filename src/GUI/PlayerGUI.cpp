//
// WallIGUI.cpp for WallIGUI.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:31:22 2014 LOEB Thomas
// Last update Thu Jun  5 17:12:59 2014 LOEB Thomas
//

#include	<iostream>
#include	"GUI/PlayerGUI.hh"

PlayerGUI::PlayerGUI() : AObject() {}

PlayerGUI::~PlayerGUI() {}

bool		PlayerGUI::initialize(glm::vec3 const &pos) {
  if (_model.load("animations/link.FBX") == false)
    return (false);

  _coord = pos;
  _position = pos;
  _scale = glm::vec3(0.01, 0.01, 0.01);
  _animations.push_back("0");
  _animations.push_back("1");
  _animations.push_back("2");
  _model.createSubAnim(0, _animations[0], 0, 28);
  _model.createSubAnim(0, _animations[1], 28, 50);
  _model.createSubAnim(0, _animations[2], 80, 120);

  return (true);
}

void		PlayerGUI::draw(gdl::AShader &shader, gdl::Clock const &clock) {
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
