# Turing Machine Simulator

## Program Format

Programs are written in `tm` files using syntax specified by the following grammar (in Antlr-like/regex syntax):
```
NUMBER : [0-9]+ ;
WS : (" " | "\t")+ ;
NL : "\n" ;
SYMBOL : [a-zA-Z0-9_!£$%^&*=#~@?] ;
STATE : SYMBOL+ ;
LEFT : "L" ;
RIGHT : "R" ;
ACCEPTING : "+" ;
REJECTING : "-" ;

// a valid program must complete the nonterminal "tm"
tm
    : states NL alphabet (NL transition)+
    ;

states
    : "states" NUMBER (NL state-def)+
    ;

state-def
    : STATE WS (ACCEPTING | REJECTING)?
    ;

alphabet
    : "alphabet" (WS SYMBOL)+
    ;

transition
    : STATE WS SYMBOL WS STATE WS SYMBOL (LEFT | RIGHT)
    ; 
```

## Building & Running

### Build

In the project root, run:
```
mkdir build && cd build && cmake .. && make
```

### Usage

Taking input from a file:
```
runtm <tm-file> <input-file> [-d|--debug] [-q|--quiet] [-h|--help] [-t|--time] [-s|--space] [-n|--n-times <n>]
```
