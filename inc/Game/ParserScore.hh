//
// ParserScore.hh for ParserScore.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Fri Jun  6 11:27:07 2014 CHAUCHET Alan
// Last update Sat Jun  7 17:16:55 2014 CHAUCHET Alan
//

#ifndef					PARSERSCORE_HH_
# define				PARSERSCORE_HH_

# include				"AParser.hh"

class					ParserScore : public AParser
{
  std::vector<std::string>		_names;
  std::vector<unsigned int>		_scores;

public:
  ParserScore(const std::vector<std::string> &);
  virtual ~ParserScore() {}
  virtual bool				checkWordsOrder(const std::string &);
  virtual void				execData(void);
  void					writeInFile(const std::string &,
						    const std::vector<std::string> &,
						    const std::vector<unsigned int> &) const;
  const std::vector<std::string>	&getNames(void) const;
  const std::vector<unsigned int>	&getScores(void) const;
  static void				sortScores(std::vector<unsigned int> &, std::vector<std::string> &);
};

#endif
