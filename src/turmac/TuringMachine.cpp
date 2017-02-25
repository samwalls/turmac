#include "turmac/TuringMachine.h"

using namespace std;

namespace turmac {

/*-------- PUBLIC --------*/

TuringMachine::TuringMachine(vector<SYMBOL> &tape, vector<STATE> &states, TransitionTable &transitions, STATE accept, STATE reject) : tape(tape) {
  init(tape, states, transitions, accept, reject);
}

SYMBOL TuringMachine::next(unsigned long n) {
  //for n, read the tape value and adjust the Turing machine's state accordingly
  for (unsigned long i = 0; i < n && (currentState == acceptState || currentState == rejectState); i++) {
    Transition t = transitions[currentState][read()];
    currentState = t.state;
    write(t.symbol);
    move(t.direction, t.moveLength);
  }
  return read();
}

string TuringMachine::getTape() {
  return string(this->tape.begin(), this->tape.end());
}

/*-------- PRIVATE --------*/

void TuringMachine::init(vector<SYMBOL> tape, vector<STATE> states, TransitionTable transitions, STATE accept, STATE reject) {
  this->tape = tape;
  this->states = states;
  this->transitions = transitions;
  this->acceptState = accept;
  this->rejectState = reject;
  this->position = 0;
}

void TuringMachine::move(Direction direction, unsigned long length) {
  switch (direction) {
    case LEFT:
      position = position == 0 ? 0 : position - length;
      break;
    case RIGHT:
      //todo: overflow?
      position += length;
      break;
  }
}

SYMBOL TuringMachine::read() {
  //we might need to resize the current view of our 'infinite' tape
  if (position >= tape.size()) {
    tape.resize(position + 1);
  }
  return tape[position];
}

void TuringMachine::write(SYMBOL v) {
  //we might need to resize the current view of our 'infinite' tape
  if (position >= tape.size()) {
    tape.resize(position + 1);
  }
  tape[position] = v;
}

}