//
// ListButton.hh for ListButton.hh in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 16:24:55 2014 abgral_f
// Last update Sat May 24 16:24:50 2014 abgral_f
//

#ifndef                 ALISTBUTTON_HH_
# define                ALISTBUTTON_HH_

#include                "AButton.hh"

class                   AListButton : public AButton
{
public:
  AListButton(float, float, float, float, fctPtr, Menu *);
  virtual ~AListButton();
  gdl::Geometry             *getGeometryRightArrow() const;
  gdl::Geometry             *getGeometryLeftArrow() const;
  bool			    getDisplayRight() const;
  bool			    getDisplayLeft() const;
  virtual void              moovArrow(bool, bool) = 0;
  virtual void              buildNewGeo() = 0;
protected:
  bool			_displayRight;
  bool			_displayLeft;
  int                   _moovArrowLeft;
  int                   _moovArrowRight;
  gdl::Geometry         *_geometryRightArrow;
  gdl::Geometry         *_geometryLeftArrow;
};

#endif
