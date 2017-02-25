#ifndef TURMAC_TURINGMACHINE_H
#define TURMAC_TURINGMACHINE_H

#include "etc.h"
#include "Transition.h"

#include <vector>
#include <map>

namespace turmac {

/// A Turing machine simulator
class TuringMachine {
 public:

  /// @throws std::invalid_argument if there are any symbols on the tape that the turing machine does not have in its
  /// set of input symbols.
  TuringMachine(std::vector<SYMBOL> &tape, std::vector<STATE> &states, TransitionTable &transitions, STATE accept, STATE reject);

  /// Run the turing machine on the input tape.
  /// @param n the maximum number of moves to try
  /// @returns the tape result after running for n steps - equivelently one could get the tape value with
  /// TuringMachine.getTape() after calling next.
  SYMBOL next(unsigned long n);

  /// \return the tape this Turing machine operates on
  std::string getTape();

 private:

  std::vector<SYMBOL> &tape;

  unsigned long position;

  std::vector<STATE> states;

  STATE currentState;

  STATE acceptState;

  STATE rejectState;

  TransitionTable transitions;

  /// initialize this Turing machine
  void init(std::vector<SYMBOL> tape, std::vector<STATE> states, TransitionTable transitions, STATE accept, STATE reject);

  void move(Direction, unsigned long length);

  SYMBOL read();

  void write(SYMBOL v);
};

}

#endif //TURMAC_TURINGMACHINE_H
