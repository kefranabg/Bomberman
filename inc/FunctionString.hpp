//
// FunctionString.hh for FunctionString.hh in /home/chauch_a/rendu/cpp_plazza
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Fri Apr 25 16:50:21 2014 CHAUCHET Alan
// Last update Fri Jun  6 11:20:30 2014 CHAUCHET Alan
//

#ifndef					FUNCTIONSTRING_HH_
# define				FUNCTIONSTRING_HH_

# include	                        <iostream>
# include		                <vector>
# include			        <sstream>

class					FunctionString
{
public:
  static std::vector<std::string>	stringToVector(const std::string &str)
  {
    std::vector<std::string>		wordTab;
    std::string				word;
    std::stringstream			ssin(str);

    while (ssin.good())
      {
	ssin >> word;
	wordTab.push_back(word);
      }
    return (wordTab);
  }

  template<typename X>
  static X				stringToVar(const std::string &str)
  {
    std::istringstream    iss(str);
    X                     val;

    iss >> val;
    return (val);
  }

  template<typename X>
  static std::string			varToString(X var)
  {
    std::ostringstream		oss;

    oss << var;
    return (oss.str());
  }

  static bool				isNum(const std::string &word)
  {
    for (unsigned int count = 0; count < word.size(); ++count)
      {
	if ((word[count] < '0' || word[count] > '9') &&
	    (word[count] != '.' || count == 0 || count == word.size() - 1))
	  return (false);
      }
    return (true);
  }

  static bool				isSimpleWord(const std::string &word)
  {
    for (unsigned int count = 0; count < word.size(); ++count)
      if (word[count] < 'a' || word[count] > 'z')
	return (false);
    return (true);
  }
};

#endif
