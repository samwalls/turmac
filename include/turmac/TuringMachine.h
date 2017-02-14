#ifndef TURMAC_TURINGMACHINE_H
#define TURMAC_TURINGMACHINE_H

#include <vector>

namespace turmac {

class TuringMachine {
 public:

  TuringMachine();

  /// Run the turing machine on the input tape.
  /// @throws std::invalid_argument if there are any symbols on the tape that the turing machine does not have in its
  /// set of input symbols.
  /// @param input the input "tape" to the turing machine
  /// @returns the final tape result of this turing machine - equivelently one could get the tape value with
  /// TuringMachine.getTape() after calling run.
  void run(std::vector<char> input);

  std::vector<char> getTape();

 protected:
  std::vector<char> tape;
};

}

#endif //TURMAC_TURINGMACHINE_H
