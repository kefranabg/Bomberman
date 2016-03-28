//
// MenuGUI.hh for MenuGUI.hh in /home/abgral_f/rendu/cpp_bomberman/inc/GUI
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Thu May 22 22:06:37 2014 abgral_f
// Last update Tue Jun  3 14:33:54 2014 abgral_f
//

#ifndef				MENUGUI_HH_
# define			MENUGUI_HH_

#include			"GUI/AGUI.hh"
#include			"Menu/Menu.hh"

class				MenuGUI : public AGUI
{
public:
  MenuGUI(Window *);
  virtual ~MenuGUI();
  virtual bool			initialize();
  virtual bool			update();
  virtual void			draw();
  void				isTextBoxButton();
  void				isArrowButton();
  void				moveCursor();
  Menu				&getMenu();
  bool				updateScreen();
private:
  Menu				_menu;
  gdl::BasicShader		_shader;
};

#endif
