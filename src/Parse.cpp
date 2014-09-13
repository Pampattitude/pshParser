#include <iostream>
#include <string>

bool	parse(std::string const &) {
  std::cout << "Woohoo!" << std::endl;
  return true;
}

extern "C" bool	parse(char const *s) {
  return parse(std::string(s));
}
