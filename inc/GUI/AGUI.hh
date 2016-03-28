//
// IGUI.hh for IGUI.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Mon May 19 14:40:29 2014 LOEB Thomas
// Last update Fri May 23 14:04:15 2014 abgral_f
//

#ifndef			AGUI_HH_
# define		AGUI_HH_

# include		"GUI/Window.hh"

class			AGUI {
protected:
  gdl::Input            _input;
  Window		*_window;

public:
  AGUI(Window *);
  virtual ~AGUI();
  virtual bool		initialize() = 0;
  virtual bool		update() = 0;
  virtual void		draw() = 0;
};

#endif			/* AGUI_HH_ */
