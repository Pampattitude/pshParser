#include <cstdlib>
#include <iostream>

#include "Parse.hpp"

int	main(void) {
  bool	success = false;

  try {
    success = parse("test");
  }
  catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Unhandled exception thrown" << std::endl;
  }

  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
