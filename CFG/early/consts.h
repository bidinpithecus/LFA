#ifndef _CONSTS_H
#define _CONSTS_H

// Group to store its content and size
typedef struct Group {
	int size;
	char* group;
} Group;

// Each production has a source and at least one destination;
typedef struct Production {
	char source;
	char* destination;
} Production;

// Context-free Grammar
typedef struct Cfg {
	Group variablesGroup;
	Group symbolsGroup;
	int numProductions;
	Production* productions;
	char initialVariable;
} Cfg;

#endif