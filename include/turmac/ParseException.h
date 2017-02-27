#ifndef TURMAC_PARSEEXCEPTION_H
#define TURMAC_PARSEEXCEPTION_H

#include <stdexcept>

namespace turmac {

/// To be thrown when there was an error parsing
class ParseException : std::runtime_error {
 public:
  ParseException(const std::string &__arg) : runtime_error(__arg) {}

  virtual const char* what() {
    return std::runtime_error::what();
  }
};

}

#endif //TURMAC_PARSEEXCEPTION_H