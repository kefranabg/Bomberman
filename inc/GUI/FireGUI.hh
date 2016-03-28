//
// FireGUI.hh for FireGUI.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Mon May 26 19:03:28 2014 LOEB Thomas
// Last update Fri Jun 13 17:29:51 2014 Maxime Manzano
//

#ifndef			FIREGUI_HH_
# define		FIREGUI_HH_

# include		"GUI/AObject.hh"

class			FireGUI : public AObject {
public:
  FireGUI(bool);
  virtual ~FireGUI();
  virtual bool		initialize(glm::vec3 const &);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);
};

#endif			/* FIREGUI_HH_ */
