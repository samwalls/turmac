#include <iostream>
#include <turmac/TuringMachine.h>

namespace turmac {

TuringMachine::TuringMachine() {
  std::string s = "hello library code!";
  this->tape = std::vector<char>(s.begin(), s.end());
}

void TuringMachine::run(std::vector<char> input) {
  //todo
}

std::vector<char> TuringMachine::getTape() {
  return this->tape;
}

}