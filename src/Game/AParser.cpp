//
// AParser.cpp for AParser.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Tue May 13 16:14:41 2014 CHAUCHET Alan
// Last update Sat Jun  7 16:10:51 2014 CHAUCHET Alan
//

#include		"Game/AParser.hh"

AParser::AParser(const std::vector<std::string> &lines)
{
  this->_lines = lines;
}

void			AParser::parseFile(void)
{
  for (unsigned int count = 0; count < this->_lines.size(); count++)
    if (!this->checkWordsOrder(this->_lines[count]))
      throw ParserError(this->_error);
  this->execData();
}

ParserError::ParserError(const std::string &msg) : std::invalid_argument(msg)
{
  std::ostringstream    oss;

  oss << "Synthax error: " << msg;
  this->_msg = oss.str();
}

ParserError::~ParserError() throw() {}

const char                      *ParserError::what() const throw()
{
  return (this->_msg.c_str());
}
