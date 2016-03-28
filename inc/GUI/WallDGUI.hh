//
// WallIGUI.hh for WallIGUI.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:29:38 2014 LOEB Thomas
// Last update Sat May 24 14:03:53 2014 LOEB Thomas
//

#ifndef			WALLDGUI_HH_
# define		WALLDGUI_HH_

# include		"GUI/AObject.hh"

class			WallDGUI : public AObject {
public:
  WallDGUI();
  virtual ~WallDGUI();
  virtual bool		initialize(glm::vec3 const &);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);
};

#endif			/* WALLDGUI_HH_ */
