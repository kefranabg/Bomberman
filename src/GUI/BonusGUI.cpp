//
// WallIGUI.cpp for WallIGUI.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:31:22 2014 LOEB Thomas
// Last update Fri Jun 13 17:31:39 2014 Maxime Manzano
//

#include	"GUI/BonusGUI.hh"

BonusGUI::BonusGUI(std::string const &pathAnimation, bool change) : AObject(change), _pathAnimation("animations/" + pathAnimation) {}

BonusGUI::~BonusGUI() {}

bool		BonusGUI::initialize(glm::vec3 const &pos) {
  if (_model.load(_pathAnimation) == false)
    return (false);

  _coord = pos;
  _position = pos;
  _scale = glm::vec3(0.02, 0.02, 0.02);
  if (_anim == true)
  _model.setCurrentAnim(0, true);
  rotate(glm::vec3(1, 0, 0), 90);
  translate(glm::vec3(0, -0.4, -0.5));

  return (true);
}

void		BonusGUI::draw(gdl::AShader &shader, gdl::Clock const &clock) {
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
