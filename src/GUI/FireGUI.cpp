//
// WallIGUI.cpp for WallIGUI.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:31:22 2014 LOEB Thomas
// Last update Fri Jun 13 17:31:28 2014 Maxime Manzano
//

#include	"GUI/FireGUI.hh"

FireGUI::FireGUI(bool change) : AObject(change) {}

FireGUI::~FireGUI() {}

bool		FireGUI::initialize(glm::vec3 const &pos) {
  if (_model.load("animations/fire.FBX") == false)
    return (false);

  _coord = pos;
  _position = pos;
  _scale = glm::vec3(0.004, 0.004, 0.004);
  if (_anim == true)
  _model.setCurrentAnim(0, false);

  return (true);
}

void		FireGUI::draw(gdl::AShader &shader, gdl::Clock const &clock) {
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
