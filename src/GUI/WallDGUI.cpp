//
// WallIGUI.cpp for WallIGUI.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:31:22 2014 LOEB Thomas
// Last update Wed May 28 14:31:07 2014 LOEB Thomas
//

#include	"GUI/WallDGUI.hh"

WallDGUI::WallDGUI() : AObject() {}

WallDGUI::~WallDGUI() {}

bool		WallDGUI::initialize(glm::vec3 const &pos) {
  if (_texture.load("texture/wall_wood.tga") == false)
    return (false);

  _coord = pos;

  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5) + pos);
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5) + pos);
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5) + pos);
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5) + pos);

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5) + pos);
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5) + pos);
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5) + pos);
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5) + pos);

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5) + pos);
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5) + pos);
  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5) + pos);
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5) + pos);

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5) + pos);
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5) + pos);
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5) + pos);
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5) + pos);

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5) + pos);
  _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5) + pos);
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5) + pos);
  _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5) + pos);

  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  // _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5) + pos);
  // _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5) + pos);
  // _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5) + pos);
  // _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5) + pos);

  // _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  // _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  // _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  // _geometry.pushUv(glm::vec2(0.0f, 1.0f));

  _geometry.build();
  return (true);
}

void		WallDGUI::draw(gdl::AShader &shader, gdl::Clock const &clock) {
  static_cast<void>(clock);
  _texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
