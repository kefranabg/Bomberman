//
// LexerKey.hh for LexerKey.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Tue May 13 12:15:50 2014 CHAUCHET Alan
// Last update Tue May 13 16:12:41 2014 CHAUCHET Alan
//

#ifndef			LEXERKEY_HH_
# define		LEXERKEY_HH_

# include		"ALexer.hh"

class			LexerKey : public ALexer
{
public:
  LexerKey();
  virtual ~LexerKey() {}
  virtual bool		checkGrammar(const std::string &);
  bool			inGrammar(const std::string &) const;
};

#endif
