#ifndef TURMAC_TRANSITION_H
#define TURMAC_TRANSITION_H

#include "etc.h"

#include <map>

namespace turmac {

/// State-transition pairs map to a transition object; this defines what to do based on current state and input.
struct Transition {

  /// the resulting state
  STATE state;

  /// the symbol to be written
  SYMBOL symbol;

  /// the direction to move in
  Direction direction;

  /// the number of cells to move by in the specified direction
  unsigned long moveLength;
};

/// A table mapping current state and input, to a Transition struct.
typedef std::map<STATE, std::map<SYMBOL, Transition>> TransitionTable;

}

#endif //RUNTM_TRANSITION_H
