#ifndef Parser_Parser_h
#define Parser_Parser_h

#include "Scanner.h"
#define MAX_SYMBOL_TABLE_SIZE 97 // Not sure what to make this, so I just made it a prime

// Struct for symbol table
typedef struct {
	int kind; 		// const = 1, int = 2, proc = 3
	char *name;	// name up to 11 chars
	int val; 		// number (ASCII value)
	int level; 		// L level
	int addr; 		// M address
} symbol;

// Enum for VM instructions
typedef enum {
    lit=1, opr, lod, sto, call, inc, jmp, jpc, sioIn, sioOut
} VMInstructions;

// Struct for code generation
typedef struct {
	int op, l, m;
} instruction;

LexemeList *LL;
int ptrLL;
symbol *symbolTable;
instruction code[MAX_CODE_LENGTH];
int cx = 0;
char token;
int g_level;
int g_addr;

int initSymbolTable();
int getTableSize();
void emit(int op, int l, int m);
void error(int errorNumber);
void getNextToken();
char *getID(int index);

// These parse their respective syntactic classes, and all of them return error codes.
int program();
int block();
int statement();
int condition();
int expression();
int term();
int factor();

#endif
/*
 1. Use = instead of :=.
 2. = must be followed by a number.
 3. Identifier must be followed by =.
 4. const, int, procedure must be followed by identifier.
 5. Semicolon or comma missing.
 6. Incorrect symbol after procedure declaration.
 7. Statement expected.
 8. Incorrect symbol after statement part in block.
 9. Period expected.
 10. Semicolon between statements missing.
 11. Undeclared identifier.
 12. Assignment to constant or procedure is not allowed.
 13. Assignment operator expected.
 14. call must be followed by an identifier.
 15. Call of a constant or variable is meaningless.
 16. then expected.
 17. Semicolon or } expected.
 18. do expected.
 19. Incorrect symbol following statement.
 20. Relational operator expected.
 21. Expression must not contain a procedure identifier.
 22. Right parenthesis missing.
 23. The preceding factor cannot begin with this symbol.
 24. An expression cannot begin with this symbol.
 25. This number is too large.
 26. := expected after Identifier
 27. 'end' expected after statement declaration
 */