//
// AParser.hh for AParser.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Tue May 13 15:58:44 2014 CHAUCHET Alan
// Last update Tue May 13 16:51:18 2014 CHAUCHET Alan
//

#ifndef				APARSER_HH_
# define			APARSER_HH_

# include			"ALexer.hh"

class				AParser
{
protected:
  std::vector<std::string>	_lines;
  std::string			_error;

public:
  AParser(const std::vector<std::string> &);
  virtual ~AParser() {}
  virtual bool			checkWordsOrder(const std::string &) = 0;
  virtual void			execData(void) = 0;
  virtual void			parseFile(void);
};

class				ParserError : public std::invalid_argument
{
  std::string			_msg;

public:
  ParserError(const std::string &);
  virtual ~ParserError() throw();
  virtual const char		*what() const throw();
};

#endif
