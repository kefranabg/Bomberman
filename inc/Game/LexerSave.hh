//
// LexerSave.hh for LexerSave.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May 14 14:42:26 2014 CHAUCHET Alan
// Last update Wed May 14 14:42:47 2014 CHAUCHET Alan
//

#ifndef			LEXERSAVE_HH_
# define		LEXERSAVE_HH_

# include		"ALexer.hh"

class			LexerSave : public ALexer
{
public:
  LexerSave();
  virtual ~LexerSave() {}
  virtual bool		checkGrammar(const std::string &);
  bool			inGrammar(const std::string &) const;
};

#endif
