//
// WallIGUI.hh for WallIGUI.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:29:38 2014 LOEB Thomas
// Last update Wed Jun 11 13:07:29 2014 LOEB Thomas
//

#ifndef			ENNEMYGUI_HH_
# define		ENNEMYGUI_HH_

# include		"GUI/AObject.hh"

class			EnnemyGUI : public AObject {
public:
  EnnemyGUI();
  virtual ~EnnemyGUI();
  virtual bool		initialize(glm::vec3 const &);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);
};

#endif			/* ENNEMYGUI_HH_ */
