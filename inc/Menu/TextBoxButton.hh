//
// TextBoxButton.hh for TextBoxButton.hh in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 17:32:38 2014 abgral_f
// Last update Fri May 23 17:38:01 2014 abgral_f
//

#ifndef                 TEXTBOXBUTTON_HH_
# define                TEXTBOXBUTTON_HH_

#include                "AButton.hh"

class                   TextBoxButton : public AButton
{
public:
  TextBoxButton(float, float, float, float, fctPtr, const std::string &, bool, Menu *);
  virtual ~TextBoxButton();
  void                      changeText(const std::string &);
  void                      setCanBeModified(bool);
  bool                      getCanBeModified() const;
  bool                      getOneCharac() const;
  virtual void              buildNewGeo();
  const std::string	    &getName() const;
private:
  std::string           _name;
  bool                  _color;
  bool                  _oneCharac;
  bool                  _canBeModified;
};

#endif
