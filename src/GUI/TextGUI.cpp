//
// TextGUI.cpp for TextGUI.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Sat Jun  7 15:57:34 2014 LOEB Thomas
// Last update Sun Jun  8 12:49:52 2014 LOEB Thomas
//

#include	<iostream>
#include	"GUI/TextGUI.hh"

TextGUI::TextGUI() : _translate(0, 0, 0), _rotate(0, 0, 0), _scale(1, 1, 1) {}

TextGUI::~TextGUI() {}

bool TextGUI::initialize(glm::vec3 const &pos, const std::string &s) {
  const static std::string letters("abcdefghijklmnopqrstuvwxyz1234567890 ");
  size_t charPos;
  double x, y;
  double tmpx = 0;
  double sizex = 0.1, sizey = 0.15;
  double middle = s.size() * sizex / 2;

  _position = pos;

  for (unsigned int i = 0; i < s.size(); ++i)
    if ((charPos = letters.find(s[i])) != std::string::npos) {
      x = (charPos % 6) * 0.166666666667;
      y = 1 - (charPos / 6) * 0.142857142857;

      _geometry.pushVertex(glm::vec3(pos.x - tmpx + middle, pos.y, pos.z));
      _geometry.pushVertex(glm::vec3(pos.x - tmpx - sizex + middle, pos.y, pos.z));
      _geometry.pushVertex(glm::vec3(pos.x - tmpx - sizex + middle, pos.y - sizey, pos.z));
      _geometry.pushVertex(glm::vec3(pos.x - tmpx + middle, pos.y - sizey, pos.z));

      _geometry.pushUv(glm::vec2(x, y));
      _geometry.pushUv(glm::vec2(x + 0.166666666667, y));
      _geometry.pushUv(glm::vec2(x + 0.166666666667, y - 0.142857142857));
      _geometry.pushUv(glm::vec2(x, y - 0.142857142857));

      tmpx += sizex;
    }

  _geometry.build();

  return (true);
}

glm::vec3 const &TextGUI::getPosition() const {
  return (_position);
}

void TextGUI::draw(gdl::AShader &shader, gdl::Texture &texture) {
  texture.bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

void TextGUI::translate(glm::vec3 const &t) {
  _translate += t;
}

void TextGUI::rotate(glm::vec3 const &r, float angle) {
  _rotate += r * angle;
}

glm::mat4 TextGUI::getTransformation() const {
  glm::mat4 transform(1);

  transform = glm::translate(transform, _translate);
  transform = glm::rotate(transform, _rotate.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotate.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotate.z, glm::vec3(0, 0, 1));
  transform = glm::scale(transform, _scale);
  return (transform);
}
