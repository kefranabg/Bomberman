//
// MapGUI.hh for MapGUI.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 12:03:17 2014 LOEB Thomas
// Last update Wed Jun 11 13:07:53 2014 LOEB Thomas
//

#ifndef			MAPGUI_HH_
# define		MAPGUI_HH_

# include		"GUI/AGUI.hh"
# include		"GUI/WallIGUI.hh"
# include		"GUI/WallDGUI.hh"
# include		"GUI/FloorGUI.hh"
# include		"GUI/PlayerGUI.hh"
# include		"GUI/EnnemyGUI.hh"
# include		"GUI/BombGUI.hh"
# include		"GUI/FireGUI.hh"
# include		"GUI/BonusGUI.hh"
# include		"GUI/TextGUI.hh"

class			MapGUI : public AGUI {
private:
  gdl::BasicShader	_shader;
  Map			*_map;
  AObject		*_player1;
  AObject		*_player2;
  std::vector<AObject*>	_players;
  std::vector<TextGUI*>	_texts;
  bool			_bombInput[2];
  bool			_startInput[2];
  std::vector< std::vector<AObject*> > _objects;
  bool			_draw;
  unsigned int		_forceDraw;
  double		_posCamX;
  double		_negCamX;
  double		_posCamY;
  double		_negCamY;
  bool			_isPlayer2;
  double		_x;
  double		_y;
  double		_middleX;
  gdl::Texture		_letters;
  unsigned int		_score[2];
  TextGUI		*_scoreGUI[2];
  unsigned int		_bombs[2];
  TextGUI		*_bombsGUI[2];

public:
  MapGUI(Window *);
  virtual ~MapGUI();
  void			reset();
  void			initObjects(int);
  virtual bool		initialize();
  virtual bool		update();
  virtual void		draw();
};

#endif			/* MAPGUI_HH_ */
