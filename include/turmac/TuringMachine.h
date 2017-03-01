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
  TuringMachine(std::vector<STATE> &states, std::vector<char> alphabet, TransitionTable &transitions, STATE accept, STATE reject);

  /// Run the turing machine on the input tape.
  /// @param n the maximum number of moves to try
  /// @returns the tape result after running for n steps - equivelently one could get the tape value with
  /// TuringMachine.getTape() after calling next.
  SYMBOL next(unsigned long n);

  /// True if and only if the current state is either accepting or rejecting
  bool isHalted();

  /// True if and only if the current state is accepting
  bool isAccepting();

  /// True if and only if the current state is rejecting
  bool isRejecting();

  /// \return the tape this Turing machine operates on
  std::string getTape();

  /// set the input tape for this turing machine
  void setTape(std::vector<SYMBOL> tape);

  /// set the input tape for this turing machine
  void setTape(std::string tape);

  /// Reset the Turing machine back to it's original state/position, using the specified input tape
  void reset(std::string tape);

  /// \returns the current tape-head position
  unsigned long getPosition();

  /// \returns a string representation of the turing machine; including the tape, and the current position on it, noting
  /// whether or not the current state is halting.
  std::string toString();

 private:

  std::vector<SYMBOL> tape;

  unsigned long position;

  std::vector<STATE> states;

  STATE initialState, currentState, acceptState, rejectState;

  std::vector<char> alphabet;

  TransitionTable transitions;

  void move(Direction, unsigned long length);

  SYMBOL read();

  void write(SYMBOL v);

  /// \returns true if the passed symbol is in the tape alphabet
  bool inAlphabet(SYMBOL symbol);
};

}

#endif //TURMAC_TURINGMACHINE_H
