//
// WallIGUI.cpp for WallIGUI.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:31:22 2014 LOEB Thomas
// Last update Sat May 24 15:21:44 2014 LOEB Thomas
//

#include	"GUI/FloorGUI.hh"

FloorGUI::FloorGUI() : AObject() {}

FloorGUI::~FloorGUI() {}

bool		FloorGUI::initialize(glm::vec3 const &pos) {
  if (_texture.load("texture/floor.tga") == false)
    return (false);

  _coord = pos;

  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5) + pos);
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5) + pos);
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5) + pos);
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5) + pos);

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.build();
  return (true);
}

void		FloorGUI::draw(gdl::AShader &shader, gdl::Clock const &clock) {
  static_cast<void>(clock);
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
