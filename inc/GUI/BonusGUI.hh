//
// FireGUI.hh for FireGUI.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Mon May 26 19:03:28 2014 LOEB Thomas
// Last update Fri Jun 13 17:30:00 2014 Maxime Manzano
//

#ifndef			BONUSGUI_HH_
# define		BONUSGUI_HH_

# include		"GUI/AObject.hh"

class			BonusGUI : public AObject {
private:
  std::string		_pathAnimation;

public:
  BonusGUI(std::string const &, bool);
  virtual ~BonusGUI();
  virtual bool		initialize(glm::vec3 const &);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);
};

#endif			/* BONUSGUI_HH_ */
