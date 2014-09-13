
#ifndef __EXCEPTION_HPP__
# define __EXCEPTION_HPP__

# include <exception>
# include <string>

# define ExceptionClass(className, text)	class	className: public std::exception {\
public:\
char const	*what() const noexcept { return text; }\
  }

ExceptionClass(InvalidEnvironmentEntry, "Invalid entry in environment");
ExceptionClass(UnknownEnvironmentEntry, "Unknown entry in environment");

class	UntypedException: public std::exception {
public:
  inline UntypedException(std::string const &s) { this->text_ = s; }
  inline char const	*what() const noexcept { return this->text_.c_str(); }

private:
  std::string	text_;
};

#endif
