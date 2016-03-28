//
// NbListButton.cpp for NbListButton.cpp in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 16:52:51 2014 abgral_f
// Last update Tue Jun  3 15:09:27 2014 abgral_f
//

#include		"Menu/NbListButton.hh"
#include		"GUI/Sound.hh"

NbListButton::NbListButton(float posX, float posY,
			   float sizeX, float sizeY,
			   fctPtr method, int min,
			   int max, Menu *menu, int value, int isMusic)
  : AListButton(posX, posY, sizeX, sizeY, method, menu),
    _min(min), _max(max)
{
  this->_type = ArrowNb;
  this->_currentValue = value;
  if (this->_currentValue < max)
    this->_displayRight = true;
  if (this->_currentValue > min)
    this->_displayLeft = true;
  this->_geometryLeftArrow = new gdl::Geometry();
  this->_geometryRightArrow = new gdl::Geometry();
  this->_geometryButton = new gdl::Geometry();
  this->_geometryLetters = new gdl::Geometry();
  this->_isMusic = isMusic;
}

NbListButton::~NbListButton() {}

void                    NbListButton::moovArrow(bool isLeft, bool isSelect)
{
  this->_displayRight = true;
  this->_displayLeft = true;
  if (isSelect == true && isLeft == true)
    {
      this->_moovArrowLeft = 3;
      if (this->_currentValue - 1 >= _min)
	{
	  this->_currentValue -= 1;
	  if (this->_isMusic == 1)
	    Sound::setVolumeMusic(this->_currentValue);
	  if (this->_isMusic == 2)
	    Sound::setVolumeSound(this->_currentValue);
	}
    }
  else if (isSelect == true)
    {
      this->_moovArrowRight = 3;
      if (this->_currentValue + 1 <= _max)
	{
	  this->_currentValue += 1;
	  if (this->_isMusic == 1)
	    Sound::setVolumeMusic(this->_currentValue);
	  if (this->_isMusic == 2)
	    Sound::setVolumeSound(this->_currentValue);
	}
    }
  else if (isLeft == true)
    this->_moovArrowLeft = 0;
  else
    this->_moovArrowRight = 0;
  if (this->_currentValue == _min)
    this->_displayLeft = false;
  if (this->_currentValue == _max)
    this->_displayRight = false;
  this->buildNewGeo();
}

void                      NbListButton::buildNewGeo()
{
  float			  z;
  std::string             result;
  std::ostringstream      convert;

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

  convert << this->_currentValue;
  result = convert.str();
  this->displayText(z, result);
  _geometryButton->build();
  _geometryLetters->build();
  _geometryLeftArrow->build();
  _geometryRightArrow->build();
}

int		NbListButton::getCurrentValue() const
{
  return (this->_currentValue);
}
