#include <turmac/Parser.h>
#include <turmac/ParseException.h>
#include <sstream>
#include <iostream>

using namespace std;

namespace turmac {

/*-------- PUBLIC --------*/

Parser::Parser(std::string filename) : input(filename) {
  this->inputSize = ifstream(filename, ifstream::ate | ifstream::binary).tellg();
  this->currentLine = 0;
}

TuringMachine Parser::parse() {
  //parsing
  vector<StateDef> states = parseStates();
  vector<SYMBOL> alphabet = parseAlphabet();
  vector<TransitionDef> transitions = parseTransition(states);
  //semantic analysis
  vector<STATE> tmStates = vector<STATE>();
  TransitionTable tmTransitions = TransitionTable();
  STATE accept, reject = STATE();
  //add states
  for (StateDef state : states) {
    if (state.isHalting && state.isAccepting)
      accept = state.name;
    else if (state.isHalting)
      reject = state.name;
    tmStates.push_back(state.name);
  }
  if (accept.size() == 0)
    throw ParseException("no accept state defined!");
  if (reject.size() == 0)
    throw ParseException("no accept state defined!");
  //add transitions
  for (TransitionDef tr : transitions) {
    tmTransitions[tr.from][tr.read] = Transition {
        state: tr.to,
        symbol: tr.write,
        direction: tr.isRight ? RIGHT : LEFT,
        moveLength: 1
    };
  }
  return TuringMachine(tmStates, alphabet, tmTransitions, accept, reject);
}

std::streamoff Parser::getInputSize() {
  return this->inputSize;
}

/*-------- PRIVATE --------*/

string Parser::getLineError(unsigned long n, string line, string info) {
  ostringstream oss = ostringstream();
  oss << "error: line " << n;
  oss << ": \"";
  oss << line << "\"";
  if (!info.empty()) {
    oss << "\n\t" + info;
  }
  return oss.str();
}

string Parser::getLineError(unsigned long n, string line) {
  return getLineError(n, line, "");
}

string Parser::readLine() {
  string line;
  if (getline(input, line))
    currentLine++;
  return line;
}

vector<string> Parser::split(string str) {
  istringstream ss(str);
  vector<string> symbols = vector<string>();
  string symbol;
  while (getline(ss, symbol, ' '))
    symbols.push_back(symbol);
  return symbols;
}

vector<StateDef> Parser::parseStates() {
  string line = readLine();
  vector<string> symbols = split(line);
  if (symbols.size() < 2)
    throw ParseException(getLineError(currentLine, line, "bad state definition header"));
  if (symbols[0] != "states")
    throw ParseException(getLineError(currentLine, line, "unexpected symbol: \"" + symbols[0] + "\""));
  //parse the number of states
  int number;
  try {
    number = stoi(symbols[1]);
  } catch (invalid_argument e) {
    throw ParseException(getLineError(currentLine, line, e.what()));
  }
  //parse list of state definitions
  vector<StateDef> states = vector<StateDef>();
  for (int i = 0; i < number; i++) {
    line = readLine();
    symbols = split(line);
    if (symbols.size() > 2 || symbols.size() < 1)
      throw ParseException(getLineError(currentLine, line, "bad state definition"));
    StateDef state = StateDef {name: symbols[0]};
    if (symbols.size() > 1 && (symbols[1] == "+" || symbols[1] == "-")) {
      state.isHalting = true;
      if (symbols[1] == "+")
        state.isAccepting = true;
    }
    states.push_back(state);
  }
  return states;
}

vector<SYMBOL> Parser::parseAlphabet() {
  string line = readLine();
  vector<string> symbols = split(line);
  if (symbols.size() < 1)
    throw ParseException(getLineError(currentLine, line, "bad alphabet definition"));
  if (symbols[0] != "alphabet")
    throw ParseException(getLineError(currentLine, line, "unexpected symbol: \"" + symbols[0] + "\""));
  //parse alphabet length
  int number;
  try {
    number = stoi(symbols[1]);
  } catch (invalid_argument e) {
    throw ParseException(getLineError(currentLine, line, e.what()));
  }
  vector<SYMBOL> alphabet = vector<SYMBOL>();
  for (int i = 2; i < 2 + number; i++) {
    char c;
    if (symbols[i].size() > 1)
      throw ParseException(getLineError(currentLine, line, "unexpected symbol: \"" + symbols[i] + "\""));
    c = symbols[i][0];
    if (c == '+' || c == '-' || c == EMPTY)
      throw ParseException(getLineError(currentLine, line, "tape symbol \'" + symbols[i] + "\' is reserved"));
    alphabet.push_back(c);
  }
  return alphabet;
}

vector<TransitionDef> Parser::parseTransition(vector<StateDef> states) {
  vector<TransitionDef> transitions = vector<TransitionDef>();
  string line;
  while (!(line = readLine()).empty()) {
    vector<string> symbols = split(line);
    TransitionDef t = TransitionDef {};
    if (symbols.size() < 4)
      throw ParseException(getLineError(currentLine, line, "bad transition definition"));
    t.from = symbols[0];
    if (!isState(t.from, states))
      throw ParseException(getLineError(currentLine, line, t.from + " is not in the list of states"));
    if (symbols[1].size() > 1)
      throw ParseException(getLineError(currentLine, line, "unexpected symbol \"" + symbols[1] + "\""));
    t.read = symbols[1][0];
    t.to = symbols[2];
    if (!isState(t.to, states))
      throw ParseException(getLineError(currentLine, line, t.to + " is not in the list of states"));
    if (symbols[3].size() > 1)
      throw ParseException(getLineError(currentLine, line, "unexpected symbol \"" + symbols[3] + "\""));
    t.write = symbols[3][0];
    if (symbols.size() > 4) {
      if (symbols[4] == "R")
        t.isRight = true;
      else if (symbols[4] != "L")
        throw ParseException(getLineError(currentLine, line, "unexpected symbol \"" + symbols[4] + "\""));
    }
    transitions.push_back(t);
  }
  if (transitions.size() <= 0)
    throw ParseException(getLineError(currentLine, line, "expected one or more transition definitions"));
  return transitions;
}

bool Parser::isState(STATE identifier, vector<StateDef> states) {
  for (auto s : states)
    if (s.name == identifier)
      return true;
  return false;
}

}