//
// AGUI.hh for AGUI.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Thu May 15 16:42:11 2014 LOEB Thomas
// Last update Thu Jun  5 12:54:14 2014 LOEB Thomas
//

#ifndef			WINDOW_HH_
# define		WINDOW_HH_

# include               <Input.hh>
# include		<Game.hh>
# include		<BasicShader.hh>
# include               <glm/glm.hpp>
# include               <glm/gtc/matrix_transform.hpp>
# include               <AShader.hh>
# include               <Texture.hh>
# include               <Geometry.hh>
# include		"Game/BomberGame.hh"
# include		"GUI/GetGDL.hh"

class			Window : public gdl::Game {
protected:
  GetGDL		_context;
  gdl::Clock		_clock;
  gdl::Input		_input;
  BomberGame		*_game;
  double		_x;
  double		_y;

public:
  Window(BomberGame *);
  virtual ~Window();
  virtual bool		initialize();
  virtual bool		update();
  virtual void		draw();
  bool			update(gdl::Input &);
  void			stop();
  void			flush();
  GetGDL const		&getContext() const;
  gdl::Clock const	&getClock() const;
  gdl::Input		getInput() const;
  BomberGame		*getGame() const;
  double		getX() const;
  double		getY() const;
};

#endif			/* WINDOW_HH_ */
