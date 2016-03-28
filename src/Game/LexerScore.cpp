//
// LexerScore.cpp for LexerScore.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Fri Jun  6 11:25:16 2014 CHAUCHET Alan
// Last update Fri Jun  6 11:25:40 2014 CHAUCHET Alan
//

#include			"Game/LexerScore.hh"

LexerScore::LexerScore()
{
}

bool				LexerScore::checkGrammar(const std::string &line)
{
  std::vector<std::string>	words = FunctionString::stringToVector(line);

  for (unsigned int count = 0; count < words.size(); count++)
    if (!FunctionString::isNum(words[count]) && !FunctionString::isSimpleWord(words[count]))
      {
    	this->_error = "Score Corrupted!";
    	return (false);
      }
  return (true);
}

bool				LexerScore::inGrammar(const std::string &word) const
{
  for (unsigned int count = 0; count < this->_grammar.size(); count++)
    if (this->_grammar[count] == word)
      return (true);
  return (false);
}
