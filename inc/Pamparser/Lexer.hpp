#ifndef __LEXER_HPP__
# define __LEXER_HPP__

# include <string>
# include <vector>

namespace Pamparser {
  class	Lexer {
  public:
    enum RuleType {
      Dictionary,	// Matches full word
      Alphabet,		// Matches list of characters in any order
      Function,		// Function returns true
    };

    bool	lexe(std::string const &) const;

    void	addRule(RuleType, char const *);
    void	addRule(RuleType, bool (*)(std::string const &));

  private:
    bool	matchesDictionary_(std::string const &, std::string const &) const;
    bool	matchesAlphabet_(std::string const &, std::string const &) const;
    bool	matchesFunction_(std::string const &, bool (*)(std::string const &)) const;

    struct	Rule {
      RuleType	type;
      union {
	char const	*str;
	bool		(*fct)(std::string const &);
      }		match;
      mutable bool	actuallyMatches = false;
      mutable bool	previousMatched = false;
    };

    std::vector<Rule*>	ruleList_;
  };
}

#endif
