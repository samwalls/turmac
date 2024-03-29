#include "turmac/TuringMachine.h"
#include <sstream>
#include <iostream>

using namespace std;

namespace turmac {

/*-------- PUBLIC --------*/

TuringMachine::TuringMachine(vector<STATE> &states, vector<SYMBOL> alphabet, TransitionTable &transitions, STATE accept, STATE reject) {
  this->tape = vector<SYMBOL>();
  this->states = states;
  this->alphabet = alphabet;
  this->transitions = transitions;
  this->acceptState = accept;
  this->rejectState = reject;
  this->position = 0;
  if (states.size() < 1) {
    throw runtime_error("cannot create turing machine with no states");
  }
  this->initialState = states[0];
  this->currentState = initialState;
}

SYMBOL TuringMachine::next(unsigned long n) {
  //for n, read the tape value and adjust the Turing machine's state accordingly
  for (unsigned long i = 0; i < n && (currentState != acceptState) && (currentState != rejectState); i++) {
    Transition t = transitions[currentState][read()];
    //assume that if the transition entry contains null information that it was not defined, subsume to a reject state
    if (t.symbol) {
      currentState = t.state;
      write(t.symbol);
      move(t.direction, t.moveLength);
    } else {
      currentState = rejectState;
    }
  }
  return read();
}

bool TuringMachine::isHalted() {
  return currentState == acceptState || currentState == rejectState;
}

bool TuringMachine::isAccepting() {
  return currentState == acceptState;
}

bool TuringMachine::isRejecting(){
  return currentState == rejectState;
}

string TuringMachine::getTape() {
  return string(this->tape.begin(), this->tape.end());
}

void TuringMachine::setTape(string tape) {
  vector<SYMBOL> t = vector<SYMBOL>(tape.begin(), tape.end());
  this->setTape(t);
}

void TuringMachine::setTape(vector<SYMBOL> tape) {
  for (SYMBOL s : tape)
    if (!inAlphabet(s))
      throw runtime_error("tape is not compatible with turing machine alphabet");
  this->tape = tape;
}

void TuringMachine::reset(string tape) {
  setTape(tape);
  this->currentState = initialState;
  this->position = 0;
}

unsigned long TuringMachine::getPosition() {
  return this->position;
}

std::string TuringMachine::toString() {
  ostringstream oss = ostringstream("");
  for (unsigned long i = 0; i < tape.size(); i++) {
    if (i == position) {
      oss << "[" << read() << "]";
    } else {
      oss << tape[i];
    }
  }
  oss << " ";
  oss << currentState;
  return oss.str();
}

/*-------- PRIVATE --------*/

void TuringMachine::move(Direction direction, unsigned long length) {
  switch (direction) {
    case LEFT:
      position = length >= position ? 0 : position - length;
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
    unsigned long sizeBefore = tape.size();
    for (unsigned long i = sizeBefore; i < position + 1; i++)
      tape.push_back(EMPTY);
  }
  return tape[position];
}

void TuringMachine::write(SYMBOL v) {
  //we might need to resize the current view of our 'infinite' tape
  if (position >= tape.size()) {
    unsigned long sizeBefore = tape.size();
    for (unsigned long i = sizeBefore; i < position + 1; i++)
      tape.push_back(EMPTY);
  }
  tape[position] = v;
}

bool TuringMachine::inAlphabet(SYMBOL symbol) {
  for (SYMBOL alpha : alphabet)
    if (alpha == symbol)
      return true;
  return false;
}

}