#include <boost/lexical_cast.hpp>

#include "Pamparser/Exception.hpp"
#include "Pamparser/Lexer.hpp"

// TMP
#include <iostream>
// EOTMP
namespace Pamparser {
  bool	Lexer::lexe(std::string const &input) const {
    for (auto it = this->ruleList_.begin(), ite = this->ruleList_.end() ; ite != it ; ++it)
      (*it)->actuallyMatches = false;

    size_t	start = std::string::npos,
      end = 0;

    while (std::string::npos == start || input.length() > start) {
      if (std::string::npos == start) {
	start = end;
	//++end;
	continue ;
      }

      for (auto it = this->ruleList_.begin(), ite = this->ruleList_.end() ; ite != it ; ++it)
	(*it)->previousMatched = (*it)->actuallyMatches;

      bool		found = false;
      if (end != input.length()) { // Matching will always fail if end is at the end of input
	std::string	extract = input.substr(start, (end - start) + 1);
	for (auto it = this->ruleList_.begin(), ite = this->ruleList_.end() ; ite != it ; ++it) {
	  switch ((*it)->type) {
	  case Dictionary:
	    (*it)->actuallyMatches = this->matchesDictionary_(extract, (*it)->match.str);
	    break ;

	  case Alphabet:
	    (*it)->actuallyMatches = this->matchesAlphabet_(extract, (*it)->match.str);
	    break ;

	  case Function:
	    (*it)->actuallyMatches = this->matchesFunction_(extract, (*it)->match.fct);
	    break ;

	  default:
	    throw UntypedException(std::string("Unknown type \"") + boost::lexical_cast<std::string>((*it)->type) + '"');
	    break ;
	  }
   
	  if ((*it)->actuallyMatches)
	    found = true;
	}
      }

      if (!found) {
	bool	hasResult = false;
	for (auto it = this->ruleList_.begin(), ite = this->ruleList_.end() ; ite != it ; ++it) {
	  if ((*it)->previousMatched) {
	    hasResult = true;
	    break ;
	  }
	  (*it)->actuallyMatches = false;
	}
	if (!hasResult)
	  throw UntypedException(std::string("No matching rule for extracted string \"") + input.substr(start, end - start + 1) + '"'); // Should be typed to be catchable

	int unsigned i = 0;
	for (auto it = this->ruleList_.begin(), ite = this->ruleList_.end() ; ite != it ; ++it) {
	  if ((*it)->previousMatched) {
	    std::cout << '"' << input.substr(start, end - start) << "\" -> rule #" << i+1 << std::endl;
	    break ;
	  }
	  ++i;
	}

	start = std::string::npos;
	//--end;
      }
      else
	++end;
    }

    return true;
  }

  void	Lexer::addRule(RuleType rt, char const *s) {
    if (Dictionary != rt && Alphabet != rt)
      throw UntypedException(std::string("Wrong string rule type \"") + boost::lexical_cast<std::string>(rt) + '"');

    Rule	*rule = new Rule;
    rule->type = rt;
    rule->match.str = s;

    this->ruleList_.push_back(rule);
  }

  void	Lexer::addRule(RuleType rt, bool (*f)(std::string const &)) {
    if (Function != rt)
      throw UntypedException(std::string("Wrong function rule type \"") + boost::lexical_cast<std::string>(rt) + '"');

    Rule	*rule = new Rule;
    rule->type = rt;
    rule->match.fct = f;

    this->ruleList_.push_back(rule);
  }


  bool	Lexer::matchesDictionary_(std::string const &input, std::string const &dict) const {
    if (dict.length() != input.length())
      return false;

    for (int unsigned i = 0 ; input.length() > i ; ++i) {
      if (dict[i] != input[i]) {
	return false;
      }
    }

    return true;
  }

  bool	Lexer::matchesAlphabet_(std::string const &input, std::string const &alpha) const {
    for (int unsigned i = 0 ; input.length() > i ; ++i) {
      bool	found = false;

      for (int unsigned j = 0 ; alpha.length() > j ; ++j) {
	if (alpha[j] == input[i]) {
	  found = true;
	  break ;
	}
      }

      if (!found)
	return false;
    }

    return true;
  }

  bool	Lexer::matchesFunction_(std::string const &input, bool (*fct)(std::string const &)) const {
    return (*fct)(input);
  }
}
