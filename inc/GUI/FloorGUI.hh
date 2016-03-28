//
// WallIGUI.hh for WallIGUI.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:29:38 2014 LOEB Thomas
// Last update Sat May 24 14:04:01 2014 LOEB Thomas
//

#ifndef			FLOORGUI_HH_
# define		FLOORGUI_HH_

# include		"GUI/AObject.hh"

class			FloorGUI : public AObject {
public:
  FloorGUI();
  virtual ~FloorGUI();
  virtual bool		initialize(glm::vec3 const &);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);
};

#endif			/* FLOORGUI_HH_ */
