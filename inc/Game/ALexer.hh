//
// ALexer.hh for ALexer.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Mon May 12 17:18:06 2014 CHAUCHET Alan
// Last update Tue May 13 16:06:25 2014 CHAUCHET Alan
//

#ifndef					ALEXER_HH_
# define				ALEXER_HH_

# include				<iostream>
# include				<fstream>
# include				<vector>
# include				<stdexcept>
# include				<sstream>
# include				"../FunctionString.hpp"

class					ALexer
{
protected:
  std::vector<std::string>		_grammar;
  std::vector<std::string>		_lines;
  std::string				_fileName;
  std::ifstream				_file;
  std::string				_error;

public:
  virtual ~ALexer();
  virtual bool					readFile(const std::string &);
  virtual void					epurLine(std::string &);
  virtual bool					checkGrammar(const std::string &) = 0;
  virtual void					checkFile(const std::string &);
  virtual const std::vector<std::string>	&getLines(void) const;
};

class					LexerError : public std::invalid_argument
{
  std::string				_msg;

public:
  LexerError(const std::string &);
  virtual ~LexerError() throw();
  virtual const char			*what() const throw();
};

#endif
