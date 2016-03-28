//
// ParserScore.cpp for ParserScore.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Fri Jun  6 11:31:08 2014 CHAUCHET Alan
// Last update Sat Jun  7 17:20:10 2014 CHAUCHET Alan
//

#include			<algorithm>
#include			"Game/ParserScore.hh"

ParserScore::ParserScore(const std::vector<std::string> &lines) : AParser(lines)
{
}

bool				ParserScore::checkWordsOrder(const std::string &line)
{
  std::vector<std::string>	words = FunctionString::stringToVector(line);

  if (words.size() != 2 || !FunctionString::isSimpleWord(words[0])
      || !FunctionString::isNum(words[1]))
    return (false);
  return (true);
}

bool				greater(int i, int j)
{
  return (i > j);
}

void				ParserScore::sortScores(std::vector<unsigned int> &scores, std::vector<std::string> &names)
{
  std::vector<unsigned int>	provValues = scores;
  std::vector<std::string>	provNames = names;

  std::sort(provValues.begin(), provValues.end(), greater);

  unsigned int count2 = 0;

  for (unsigned int count = 0; count < provValues.size(); ++count)
    {
      count2 = 0;
      while (count2 < scores.size() && scores[count2] != provValues[count])
	count2++;
      if (count2 < scores.size())
	names[count] = provNames[count2];
    }
  scores = provValues;
}

void				ParserScore::execData(void)
{
  std::vector<std::string>	words;

  this->_names.clear();
  this->_scores.clear();
  for (unsigned int count = 0; count < this->_lines.size(); count++)
    {
      words = FunctionString::stringToVector(this->_lines[count]);
      this->_names.push_back(words[0]);
      this->_scores.push_back(FunctionString::stringToVar<unsigned int>(words[1]));
    }
  this->_scores.resize(3);
  this->_names.resize(3);
  ParserScore::sortScores(this->_scores, this->_names);
}

void				ParserScore::writeInFile(const std::string &fileName,
							 const std::vector<std::string> &names,
							 const std::vector<unsigned int> &scores) const
{
  std::ofstream			file;

  file.open(fileName.c_str(), std::ofstream::out | std::ofstream::trunc);
  if (file.fail() || names.size() != scores.size())
    return ;
  for (unsigned int count = 0; count < names.size(); ++count)
    file << names[count] << " " << FunctionString::varToString<unsigned int>(scores[count]) << std::endl;
}

const std::vector<std::string>	&ParserScore::getNames(void) const
{
  return (this->_names);
}

const std::vector<unsigned int>	&ParserScore::getScores(void) const
{
  return (this->_scores);
}
