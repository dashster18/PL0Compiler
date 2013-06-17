#ifndef Parser_Parser_h
#define Parser_Parser_h

#include "Scanner.h"

// Struct for symbol table
typedef struct {
	int kind; 		// const = 1, int = 2, proc = 3
	char name[10];	// name up to 11 chars
	int val; 		// number (ASCII value)
	int level; 		// L level
	int addr; 		// M address
} symbol;

// Struct for code generation
typedef struct {
	int op, l, m;
} instruction;

symbol symbolTable[MAX_SYMBOL_TABLE_SIZE];
instruction code[MAX_CODE_LENGTH];
int cx = 0;

void emit(int op, int l, int m);
void error(int errorNumber);

#endif
