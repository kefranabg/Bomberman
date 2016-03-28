//
// Cinematic.hh for Cinematic.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Thu Jun  5 16:31:18 2014 LOEB Thomas
// Last update Thu Jun  5 18:39:25 2014 LOEB Thomas
//

#ifndef			CINEMATIC_HH_
# define		CINEMATIC_HH_

# include		"Model.hh"
# include		"GUI/AGUI.hh"
# include		"GUI/AObject.hh"

class			Cinematic : public AGUI {
private:
  gdl::Model		_model;
  gdl::BasicShader	_shader;
  unsigned int		_stop;
  gdl::Texture		_textureBackground;
  gdl::Geometry		_geometryBackground;

public:
  Cinematic(Window *);
  virtual ~Cinematic();
  virtual bool		initialize();
  virtual bool		update();
  virtual void		draw();
};

#endif			/* CINEMATIC_HH_ */
