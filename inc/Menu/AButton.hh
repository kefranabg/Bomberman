//
// AButton.hh for AButton.hh in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 13:26:11 2014 abgral_f
// Last update Sat May 24 14:49:15 2014 abgral_f
//

#ifndef                 ABUTTON_HH_
# define                ABUTTON_HH_


#include                <iostream>
#include                <string>
#include                <Geometry.hh>
#include                <glm/glm.hpp>
#include                <vector>


class                   Menu;

class			AButton
{
public:
  typedef void          (Menu::*fctPtr)(void);
public:
  typedef enum
    {
      Normal,
      Arrow,
      ArrowNb,
      TextBox
    } buttonType;
public:
  AButton(float, float, float, float, fctPtr, Menu *);
  virtual ~AButton();
  fctPtr                getMethod() const;
  bool                  getIsSelect() const;
  buttonType            getType() const;
  void                  setIsSelect(bool);
  gdl::Geometry         *getGeometryButton() const;
  gdl::Geometry         *getGeometryLetters() const;
  void                  moovTextCursor(float, float);
  void                  displayText(float, const std::string &);
  static bool           getC(char, std::vector<glm::vec2 *> &);
  virtual void          buildNewGeo() = 0;
protected:
  buttonType            _type;
  float                 _textCursorX;
  float                 _textCursorY;
  float                 _posX;
  float                 _posY;
  float                 _sizeX;
  float                 _sizeY;
  bool                  _isSelect;
  fctPtr                _method;
  Menu                  *_menu;
  gdl::Geometry         *_geometryButton;
  gdl::Geometry         *_geometryLetters;
};

#endif
