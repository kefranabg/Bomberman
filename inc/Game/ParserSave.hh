//
// ParserSave.hh for ParserSave.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May 14 15:02:02 2014 CHAUCHET Alan
// Last update Mon May 19 14:26:17 2014 CHAUCHET Alan
//

#ifndef					PARSERSAVE_HH_
# define				PARSERSAVE_HH_

# include				"AParser.hh"
# include				"Map.hh"
# include				"APlayer.hh"

class					BomberGame;

class					ParserSave : public AParser
{
  typedef bool				(ParserSave::*funcSave)(const std::vector<std::string> &);

  std::vector<std::string>		_words1;
  std::vector<std::string>		_words2;
  std::vector<std::string>		_words3;
  e_typeObj				_correspObj[5];
  Map					*_map;
  std::vector<Box*>			_boxs;
  std::vector<APlayer*>			_players;
  funcSave				_functionsCreate[3];
  unsigned int				_mapSizeX;
  unsigned int				_mapSizeY;
  BomberGame				*_game;

  bool					createIA(const std::vector<std::string> &);
  bool					createHumanPlayer(const std::vector<std::string> &);

public:
  ParserSave(const std::vector<std::string> &, BomberGame *);
  virtual ~ParserSave() {}
  virtual bool				checkWordsOrder(const std::string &);
  virtual void				execData(void);
  void					writeInFile(const Map *, const std::vector<APlayer*> &, const std::string &) const;
  Map					*getMap(void) const;
  const std::vector<APlayer*>		&getPlayers(void) const;
  bool					createMap(const std::vector<std::string> &);
  bool					createBox(const std::vector<std::string> &);
  bool					createPlayer(const std::vector<std::string> &);
  void					clear(void);
};

#endif
