#ifndef TURMAC_ETC_H
#define TURMAC_ETC_H

/*
 * Small types and various constants for use throughout the turmac namespace.
 */

namespace turmac {

/// Type of symbol which tape cells contain, and Turing machine's deal with.
typedef wchar_t SYMBOL;

/// The blank tape cell.
static const SYMBOL EMPTY = 0;

/// The type of states in a Turing machine.
typedef std::string STATE;

/// Directions a Turing machine can move in.
enum Direction {
  LEFT,
  RIGHT
};

}

#endif //TURMAC_ETC_H
