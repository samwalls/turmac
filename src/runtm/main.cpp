#include <iostream>
#include <turmac.h>

int main() {
  turmac::TuringMachine *m = new turmac::TuringMachine();
  auto tape = m->getTape();
  std::cout << std::string(tape.begin(), tape.end()) << std::endl;
}
