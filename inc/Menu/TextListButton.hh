//
// TextListButton.hh for TextListButton.hh in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 17:01:38 2014 abgral_f
// Last update Fri May 23 16:00:05 2014 abgral_f
//

#ifndef                 TEXTLISTBUTTON_HH_
# define                TEXTLISTBUTTON_HH_

#include                "AListButton.hh"

class                   TextListButton : public AListButton
{
public:
  TextListButton(float, float, float, float, fctPtr, const std::vector<std::string> &, Menu *);
  virtual ~TextListButton();
  virtual void              moovArrow(bool, bool);
  virtual void              buildNewGeo();
  const std::vector<std::string> &getList() const;
  int				getCursorList() const;
private:
  std::vector<std::string>  _list;
  int			    _cursorList;
};

#endif
