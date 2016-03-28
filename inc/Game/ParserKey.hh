//
// ParserKey.cpp for ParserKey.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Tue May 13 16:24:56 2014 CHAUCHET Alan
// Last update Wed May 14 12:38:21 2014 CHAUCHET Alan
//

#ifndef					PARSERKEY_HH_
# define				PARSERKEY_HH_

# include				"AParser.hh"
# include				"Key.hh"

class					ParserKey : public AParser
{
  std::vector<std::string>		_words1;
  std::vector<std::string>		_words2;
  std::string				_words3;
  std::vector<e_keyType>		_keyType;

public:
  ParserKey(const std::vector<std::string> &);
  virtual ~ParserKey() {}
  virtual bool				checkWordsOrder(const std::string &);
  virtual void				execData(void);
  unsigned int				whichPlace(const std::string &) const;
  e_keyType				whichCommand(const std::string &) const;
  void					writeInFile(const std::string &) const;
};

#endif
