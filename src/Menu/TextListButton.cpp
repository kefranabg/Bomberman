//
// TextListButton.cpp for TextListButton.cpp in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 17:03:03 2014 abgral_f
// Last update Sun Jun  8 13:54:29 2014 LOEB Thomas
//

#include		"Menu/TextListButton.hh"

TextListButton::TextListButton(float posX, float posY,
			       float sizeX, float sizeY,
			       fctPtr method, const std::vector<std::string> &list,
			       Menu *menu)
  : AListButton(posX, posY, sizeX, sizeY, method, menu),
    _list(list)
{
  this->_type = Arrow;
  this->_cursorList = 0;
  if (list.size() == 0 || list.size() == 1)
    _displayRight = false;
  this->_geometryLeftArrow = new gdl::Geometry();
  this->_geometryRightArrow = new gdl::Geometry();
  this->_geometryButton = new gdl::Geometry();
  this->_geometryLetters = new gdl::Geometry();
}

TextListButton::~TextListButton() {}

void                      TextListButton::buildNewGeo()
{
  float                 z = 0;

  if (!this->_geometryButton)
    delete this->_geometryButton;
  if (!this->_geometryLetters)
    delete this->_geometryLetters;
  if (!this->_geometryRightArrow)
    delete this->_geometryRightArrow;
  if (!this->_geometryLeftArrow)
    delete this->_geometryLeftArrow;
  this->_geometryLeftArrow = new gdl::Geometry();
  this->_geometryRightArrow = new gdl::Geometry();
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

  _geometryRightArrow->pushVertex(glm::vec3(_posX + 7 + _sizeX, _posY, z + _moovArrowRight));
  _geometryRightArrow->pushVertex(glm::vec3(_posX + 2 + _sizeX, _posY, z + _moovArrowRight));
  _geometryRightArrow->pushVertex(glm::vec3(_posX + 2 + _sizeX, _posY - _sizeY, z + _moovArrowRight));
  _geometryRightArrow->pushVertex(glm::vec3(_posX + 7 + _sizeX, _posY - _sizeY, z + _moovArrowRight));

  _geometryRightArrow->pushUv(glm::vec2(0.0, 1));
  _geometryRightArrow->pushUv(glm::vec2(1, 1));
  _geometryRightArrow->pushUv(glm::vec2(1, 0.0));
  _geometryRightArrow->pushUv(glm::vec2(0.0, 0.0));

  _geometryLeftArrow->pushVertex(glm::vec3(_posX - 7, _posY, z + _moovArrowLeft));
  _geometryLeftArrow->pushVertex(glm::vec3(_posX - 2, _posY, z + _moovArrowLeft));
  _geometryLeftArrow->pushVertex(glm::vec3(_posX - 2, _posY - _sizeY, z + _moovArrowLeft));
  _geometryLeftArrow->pushVertex(glm::vec3(_posX - 7, _posY - _sizeY, z + _moovArrowLeft));

  _geometryLeftArrow->pushUv(glm::vec2(0.0, 1));
  _geometryLeftArrow->pushUv(glm::vec2(1, 1));
  _geometryLeftArrow->pushUv(glm::vec2(1, 0.0));
  _geometryLeftArrow->pushUv(glm::vec2(0.0, 0.0));
  if (this->_list.size() != 0)
    this->displayText(z, this->_list[this->_cursorList]);
  else
    this->displayText(z, " ");
  _geometryButton->build();
  _geometryLetters->build();
  _geometryLeftArrow->build();
  _geometryRightArrow->build();
}

void                    TextListButton::moovArrow(bool isLeft, bool isSelect)
{
  if (this->_list.size() != 0
      && this->_list.size() != 1)
    {
      this->_displayRight = true;
      this->_displayLeft = true;
    }
  if (isSelect == true && isLeft == true)
    {
      this->_moovArrowLeft = 3;
      if (this->_cursorList - 1 >= 0)
	this->_cursorList -= 1;
    }
  else if (isSelect == true)
    {
      this->_moovArrowRight = 3;
      if (this->_list.size() > static_cast<unsigned int>(this->_cursorList + 1))
	this->_cursorList += 1;
    }
  else if (isLeft == true)
    this->_moovArrowLeft = 0;
  else
    this->_moovArrowRight = 0;
  if (this->_list.size() == static_cast<unsigned int>(this->_cursorList + 1))
    this->_displayRight = false;
  if (this->_cursorList == 0)
    this->_displayLeft = false;
  this->buildNewGeo();
}

const std::vector<std::string> &TextListButton::getList() const
{
  return (this->_list);
}

int                           TextListButton::getCursorList()const
{
  return (this->_cursorList);
}
