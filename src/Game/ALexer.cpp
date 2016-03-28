//
// ALexer.cpp for ALexer.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Tue May 13 12:17:56 2014 CHAUCHET Alan
// Last update Sat Jun  7 16:10:10 2014 CHAUCHET Alan
//

#include			"Game/ALexer.hh"

ALexer::~ALexer()
{
  if (this->_file.is_open())
    this->_file.close();
}

bool				ALexer::readFile(const std::string &fileName)
{
  std::string		line;

  this->_file.open(fileName.c_str(), std::ifstream::in);
  if (this->_file.fail())
    return (false);
  while (std::getline(this->_file, line))
    if (line.size() > 0)
      this->_lines.push_back(line);
  if (!this->_lines.size())
    return (false);
  return (true);
}

void				ALexer::epurLine(std::string &line)
{
  unsigned int          count;

  for (count = 0; count < line.size(); count++)
    if (line[count] == '\t')
      line[count] = ' ';
  while (line.size() && line[0] == ' ')
    line.erase(0, 1);
  while (line.size() && line[line.size() - 1] == ' ')
    line.erase(line.size() - 1, 1);
  count = 0;
  while (count < line.size())
    {
      if (line[count] == ' ' && line[count + 1] == ' ')
        line.erase(count + 1, 1);
      else
        count++;
    }
}

void				ALexer::checkFile(const std::string &fileName)
{
  this->_fileName = fileName;
  if (!this->readFile(fileName))
    return ;
  for (unsigned int count = 0; count < this->_lines.size(); count++)
    {
      this->epurLine(this->_lines[count]);
      if (!this->checkGrammar(this->_lines[count]))
	throw LexerError(this->_error);
    }
}

const std::vector<std::string>	&ALexer::getLines(void) const
{
  return (this->_lines);
}

LexerError::LexerError(const std::string &msg) : std::invalid_argument(msg)
{
  std::ostringstream    oss;

  oss << "Lexical error: " << msg;
  this->_msg = oss.str();
}

LexerError::~LexerError() throw() {}

const char                      *LexerError::what() const throw()
{
  return (this->_msg.c_str());
}
