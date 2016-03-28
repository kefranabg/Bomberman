//
// WallIGUI.hh for WallIGUI.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:29:38 2014 LOEB Thomas
// Last update Fri Jun 13 17:19:33 2014 Maxime Manzano
//

#ifndef			BOMBGUI_HH_
# define		BOMBGUI_HH_

# include		"GUI/AObject.hh"

class			BombGUI : public AObject {
public:
  BombGUI();
  BombGUI(bool);
  virtual ~BombGUI();
  virtual bool		initialize(glm::vec3 const &);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);
};

#endif			/* BOMBGUI_HH_ */
