//
// WallIGUI.hh for WallIGUI.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:29:38 2014 LOEB Thomas
// Last update Sat May 24 14:03:44 2014 LOEB Thomas
//

#ifndef			WALLIGUI_HH_
# define		WALLIGUI_HH_

# include		"GUI/AObject.hh"

class			WallIGUI : public AObject {
public:
  WallIGUI();
  virtual ~WallIGUI();
  virtual bool		initialize(glm::vec3 const &);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);
};

#endif			/* WALLIGUI_HH_ */
