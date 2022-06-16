#ifndef _CONSTS_H
#define _CONSTS_H

typedef struct States {
	int numStates;
	int *states;
} States;

typedef struct Symbols {
	int numSymbols;
	char *symbols;
} Symbols;

typedef struct Automata {
	Symbols *symbols;
	States *states;
	States *finalStates;
	int inicialState;
	int **transitionFunction;
	int numTransitions;
} Automata;

#endif