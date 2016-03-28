//
// LexerScore.hh for LexerScore.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Fri Jun  6 11:24:49 2014 CHAUCHET Alan
// Last update Fri Jun  6 11:25:02 2014 CHAUCHET Alan
//

#ifndef			LEXERSCORE_HH_
# define		LEXERSCORE_HH_

# include		"ALexer.hh"

class			LexerScore : public ALexer
{
public:
  LexerScore();
  virtual ~LexerScore() {}
  virtual bool		checkGrammar(const std::string &);
  bool			inGrammar(const std::string &) const;
};

#endif
