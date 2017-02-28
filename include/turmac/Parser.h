#ifndef TURMAC_PARSER_H
#define TURMAC_PARSER_H

#include "TuringMachine.h"

#include <fstream>

namespace turmac {

struct StateDef {
  STATE name;
  /// true if the state is accepting or rejecting (halting)
  bool isHalting;
  ///should be ignored if isHalting is false; is true if the state is accepting, false if rejecting
  bool isAccepting;
};

struct TransitionDef {
  STATE from;
  char read;
  STATE to;
  char write;
  ///true if the transition moves right, false if left
  bool isRight;
};

/// Parser for turmac Turing machine
class Parser {
 public:

  /// \param the path to a file to parse from
  Parser(std::string filename);

  /// \return the first parsed TuringMachine object from the parser's input stream
  TuringMachine parse();

  /// \return the size of the input
  std::streamoff getInputSize();

 private:

  typedef unsigned long LENGTH;

  std::streamoff inputSize;

  std::ifstream input;

  unsigned long currentLine;

  std::string getLineError(unsigned long n, std::string line);

  std::string getLineError(unsigned long n, std::string line, std::string info);

  std::string readLine();

  std::vector<std::string> split(std::string str);

  std::vector<StateDef> parseStates();

  std::vector<SYMBOL> parseAlphabet();

  /// \return matched length; state from; read symbol; state to; write symbol; true if right, false if left.
  std::vector<TransitionDef> parseTransition(std::vector<StateDef> states);

  /// \return true if the state represented by the identifier exists for the list of defined states
  bool isState(STATE identifier, std::vector<StateDef> states);
};

}

#endif //TURMAC_PARSER_H
