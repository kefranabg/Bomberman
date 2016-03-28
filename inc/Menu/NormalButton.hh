//
// NormalButton.hh for NormalButton.hh in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 15:03:13 2014 abgral_f
// Last update Fri May 23 11:46:28 2014 abgral_f
//

#ifndef                 NORMALBUTTON_HH_
# define                NORMALBUTTON_HH_

#include		"AButton.hh"

class			NormalButton : public AButton
{
public:
  NormalButton(float, float, float, float, fctPtr, const std::string &, Menu *);
  virtual ~NormalButton();
  virtual void			buildNewGeo();
private:
  std::string           _name;
};

#endif
