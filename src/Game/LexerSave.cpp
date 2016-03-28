//
// LexerSave.cpp for LexerSave.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Wed May 14 14:42:59 2014 CHAUCHET Alan
// Last update Sat Jun  7 17:52:07 2014 CHAUCHET Alan
//

#include			"Game/LexerSave.hh"

LexerSave::LexerSave()
{
  this->_grammar.push_back("MAP");
  this->_grammar.push_back("BOX");
  this->_grammar.push_back("WALL_D");
  this->_grammar.push_back("WALL_I");
  this->_grammar.push_back("BONUS_NEW_BOMB");
  this->_grammar.push_back("BONUS_ADD_RANGE");
  this->_grammar.push_back("BONUS_SPEED_UP");
  this->_grammar.push_back("PLAYER");
  this->_grammar.push_back("PLAYER1");
  this->_grammar.push_back("PLAYER2");
  this->_grammar.push_back("IA");
}

bool				LexerSave::checkGrammar(const std::string &line)
{
  std::vector<std::string>	words = FunctionString::stringToVector(line);

  for (unsigned int count = 0; count < words.size(); count++)
    if (!this->inGrammar(words[count]) && !FunctionString::isNum(words[count]) && !FunctionString::isSimpleWord(words[count]))
      {
    	this->_error = "Save Corrupted!";
    	return (false);
      }
  return (true);
}

bool				LexerSave::inGrammar(const std::string &word) const
{
  for (unsigned int count = 0; count < this->_grammar.size(); count++)
    if (this->_grammar[count] == word)
      return (true);
  return (false);
}
