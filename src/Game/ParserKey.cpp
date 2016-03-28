//
// ParserKey.cpp for ParserKey.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Tue May 13 16:31:54 2014 CHAUCHET Alan
// Last update Wed May 14 14:15:58 2014 CHAUCHET Alan
//

#include			"Game/ParserKey.hh"

ParserKey::ParserKey(const std::vector<std::string> &lines) : AParser(lines)
{
  this->_words1.push_back("PLAYER1");
  this->_words1.push_back("PLAYER2");
  this->_words2.push_back("KEY_UP");
  this->_words2.push_back("KEY_DOWN");
  this->_words2.push_back("KEY_LEFT");
  this->_words2.push_back("KEY_RIGHT");
  this->_words2.push_back("KEY_BOMB");
  this->_words2.push_back("KEY_PAUSE");
  this->_words3 = "=";
  this->_keyType.push_back(KEY_UP);
  this->_keyType.push_back(KEY_DOWN);
  this->_keyType.push_back(KEY_LEFT);
  this->_keyType.push_back(KEY_RIGHT);
  this->_keyType.push_back(KEY_BOMB);
  this->_keyType.push_back(KEY_PAUSE);
}

bool				ParserKey::checkWordsOrder(const std::string &line)
{
  std::vector<std::string>	words = FunctionString::stringToVector(line);
  unsigned int			pos;

  for (unsigned int count = 0; count < words.size(); count++)
    if ((pos = this->whichPlace(words[count])) != count)
      {
	this->_error = "Badly placed '" + words[count] + "'. It should be the " +
	  FunctionString::varToString<int>(pos + 1) + " word of the line.";
	return (false);
      }
  return (true);
}

unsigned int			ParserKey::whichPlace(const std::string &word) const
{
  for (unsigned int count = 0; count < this->_words1.size(); count++)
    if (this->_words1[count] == word)
      return (0);
  for (unsigned int count = 0; count < this->_words2.size(); count++)
    if (this->_words2[count] == word)
      return (1);
  if (this->_words3 == word)
    return (2);
  return (3);
}

void				ParserKey::execData(void)
{
  std::vector<std::string>	words;
  e_keyType			pos;

  for (unsigned int count = 0; count < this->_lines.size(); count++)
    {
      words = FunctionString::stringToVector(this->_lines[count]);
      pos = this->whichCommand(words[1]);
      if (words[0] == "PLAYER1")
	Key::setKeyPlayer1(pos, FunctionString::stringToVar<int>(words[3]));
      else if (words[0] == "PLAYER2")
	Key::setKeyPlayer2(pos, FunctionString::stringToVar<int>(words[3]));
    }
}

e_keyType			ParserKey::whichCommand(const std::string &word) const
{
  for (unsigned int count = 0; count < this->_words2.size(); count++)
    if (this->_words2[count] == word)
      return (this->_keyType[count]);
  return (BAD_KEY);
}

void				ParserKey::writeInFile(const std::string &fileName) const
{
  std::ofstream			file;
  int				key;

  file.open(fileName.c_str(), std::ofstream::out | std::ofstream::trunc);
  if (file.fail())
    return ;
  for (unsigned int count = 0; count < this->_words1.size(); count++)
    for (unsigned int count2 = 0; count2 < this->_words2.size(); count2++)
      {
	if (this->_words1[count] == "PLAYER1")
	  key = Key::getKeyPlayer1(static_cast<e_keyType>(count2));
	else if (this->_words1[count] == "PLAYER2")
	  key = Key::getKeyPlayer2(static_cast<e_keyType>(count2));
	file << this->_words1[count] << " " << this->_words2[count2] << " = " << key << std::endl;
      }
}
