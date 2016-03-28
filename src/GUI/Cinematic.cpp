//
// Cinematic.cpp for Cinematic.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Thu Jun  5 16:37:20 2014 LOEB Thomas
// Last update Fri Jun 13 15:12:58 2014 Maxime Manzano
//

#include "GUI/Cinematic.hh"

Cinematic::Cinematic(Window *window) : AGUI(window) {}

Cinematic::~Cinematic() {}

bool Cinematic::initialize() {
  if (!_model.load("animations/link_intro.FBX") ||
      !_shader.load("LibBomberman_linux_x64/shaders/basic.fp", GL_FRAGMENT_SHADER) ||
      !_shader.load("LibBomberman_linux_x64/shaders/basic.vp", GL_VERTEX_SHADER) ||
      !_shader.build() ||
      !_textureBackground.load("texture/Menu.tga"))
    return (false);
  std::cout << "Model Loaded" << std::endl;
  glEnable(GL_DEPTH_TEST);
  glm::mat4 projection = static_cast<glm::mat4>(glm::perspective(40.0, _window->getX() / _window->getY(), 0.1, 100.0));
  glm::mat4 transformation = glm::lookAt(glm::vec3(0, 5, 15), glm::vec3(0, 5, 0), glm::vec3(0, 1, 0));
  _shader.bind();
  _shader.setUniform("projection", projection);
  _shader.setUniform("view", transformation);
  _model.createSubAnim(0, "intro", 25, 150);
  _model.setCurrentSubAnim("intro", false);
  _stop = 250;

  _geometryBackground.pushVertex(glm::vec3(-49, 43, -85));
  _geometryBackground.pushVertex(glm::vec3(49, 43, -85));
  _geometryBackground.pushVertex(glm::vec3(49, -33, -85));
  _geometryBackground.pushVertex(glm::vec3(-49, -33, -85));

  _geometryBackground.pushUv(glm::vec2(0.0, 1));
  _geometryBackground.pushUv(glm::vec2(1, 1));
  _geometryBackground.pushUv(glm::vec2(1, 0.0));
  _geometryBackground.pushUv(glm::vec2(0.0, 0.0));

  _geometryBackground.build();
  return (true);
}

bool Cinematic::update() {
  if (_window->update(_input) == false)
    _window->getGame()->setQuit(true);
  else if (_input.getKey(SDLK_ESCAPE) || _stop == 0) {
    glDisable(GL_DEPTH_TEST);
    return (false);
  }
  --_stop;
  return (true);
}

void Cinematic::draw() {
  _window->draw();

  glm::mat4 transform(1);

  _textureBackground.bind();
  _geometryBackground.draw(_shader, transform, GL_QUADS);

  transform = glm::translate(transform, glm::vec3(0, 2, 0));
  transform = glm::scale(transform, glm::vec3(0.1, 0.1, 0.1));
  _model.draw(_shader, transform, _window->getClock().getElapsed());

  _window->flush();
}
