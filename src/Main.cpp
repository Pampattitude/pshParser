#include <cstdlib>
#include <iostream>

#include "Pamparser/Lexer.hpp"

int	main(void) {
  bool	success = false;

  try {
    {
      Pamparser::Lexer	lexer;

      using Lex = Pamparser::Lexer;
      lexer.addRule(Lex::Dictionary, "test");
      lexer.addRule(Lex::Alphabet, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
      lexer.addRule(Lex::Alphabet, "0123456789");
      lexer.addRule(Lex::Alphabet, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-");
      lexer.addRule(Lex::Alphabet, "(");
      lexer.addRule(Lex::Alphabet, ")");
      lexer.addRule(Lex::Alphabet, " \t\r\n");

      success = lexer.lexe("this is a 10 (simple) test 9lol");
    }

    std::cout << std::endl << std::endl;

    {
      Pamparser::Lexer	lexer;

      using Lex = Pamparser::Lexer;
      lexer.addRule(Lex::Alphabet, ";");
      lexer.addRule(Lex::Dictionary, "&&");
      lexer.addRule(Lex::Dictionary, "||");
      lexer.addRule(Lex::Alphabet, "|");
      lexer.addRule(Lex::Alphabet, ">");

      lexer.addRule(Lex::Function, [] (std::string const &str) {
	  int unsigned i = 0;
	  for ( ; str[i] == '-' || str[i] == '+' ; ++i)
	    ;

	  char const *alphabet = "0123456789";
	  for ( ; str.length() > i ; ++i) {
	    int unsigned j = 0;

	    for ( ; alphabet[j] ; ++j)
	      if (alphabet[j] == str[i])
		break;

	    if (!alphabet[j])
	      return false;
	  }

	  return true;
	});
      lexer.addRule(Lex::Alphabet, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_");

      lexer.addRule(Lex::Alphabet, " \t\r\n");

      success = success && lexer.lexe("ls -laG 12 > file ;cat test||echo|cat -e");
    }
  }
  catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
  }
  // TMP
  catch (char const * const e) {
    std::cerr << e << std::endl;
  }
  // EOTMP
  catch (...) {
    std::cerr << "Unhandled exception thrown" << std::endl;
  }

  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
