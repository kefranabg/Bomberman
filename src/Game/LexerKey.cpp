//
// LexerKey.hh<2> for LexerKey.hh<2> in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Tue May 13 14:39:06 2014 CHAUCHET Alan
// Last update Tue May 13 16:19:51 2014 CHAUCHET Alan
//

#include			"Game/LexerKey.hh"

LexerKey::LexerKey()
{
  this->_grammar.push_back("PLAYER1");
  this->_grammar.push_back("PLAYER2");
  this->_grammar.push_back("KEY_UP");
  this->_grammar.push_back("KEY_DOWN");
  this->_grammar.push_back("KEY_LEFT");
  this->_grammar.push_back("KEY_RIGHT");
  this->_grammar.push_back("KEY_BOMB");
  this->_grammar.push_back("KEY_PAUSE");
  this->_grammar.push_back("=");
}

bool				LexerKey::checkGrammar(const std::string &line)
{
  std::vector<std::string>	words = FunctionString::stringToVector(line);

  for (unsigned int count = 0; count < words.size(); count++)
    if (!this->inGrammar(words[count]) && !FunctionString::isNum(words[count]))
      {
    	this->_error = "unknown word '" + words[count] +
    	  "' in file '" + this->_fileName + "' used to parse key.";
    	return (false);
      }
  return (true);
}

bool				LexerKey::inGrammar(const std::string &word) const
{
  for (unsigned int count = 0; count < this->_grammar.size(); count++)
    if (this->_grammar[count] == word)
      return (true);
  return (false);
}
