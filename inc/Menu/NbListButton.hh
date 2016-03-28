//
// ButtonNbList.hh for ButtonNbList.hh in /home/abgral_f/dev/bomberman
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 16:21:20 2014 abgral_f
// Last update Mon Jun  2 17:27:07 2014 CHAUCHET Alan
//

#ifndef                 NBLISTBUTTON_HH_
# define                NBLISTBUTTON_HH_

#include		<sstream>
#include                "AListButton.hh"

class                   NbListButton : public AListButton
{
public:
  NbListButton(float, float, float, float, fctPtr, int, int, Menu *, int, int isMusic = 0);
  virtual ~NbListButton();
  virtual void              moovArrow(bool, bool);
  virtual void              buildNewGeo();
  int			    getCurrentValue() const;
private:
  int                   _min;
  int                   _max;
  int                   _currentValue;
  int			_isMusic;
};

#endif
