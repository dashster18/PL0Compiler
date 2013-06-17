#ifndef Parser_LexicalAnalyzer_h
#define Parser_LexicalAnalyzer_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_MAX_FILE_SIZE 1 << 10 // 1024
#define MAX_ID_LENGTH 11
#define MAX_NUMBER_DIGITS 5
#define NUMBER_RESERVED_WORDS 13
#define MAX_CODE_LENGTH 500

// Enum for symbol types
typedef enum {
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, intsym, procsym, outsym,
    insym , elsesym
} token_type;

//Used to store the lexemes
typedef struct {
	int *list;
    long size;
    long numId;
	char **symbols;
} LexemeList;

char *word[] = {"const", "int", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"};
int wordSymbol[] = {constsym, intsym, procsym, callsym, beginsym, endsym, ifsym, thensym, elsesym, whilesym, dosym, insym, outsym, oddsym};
int ssym[256];
int CURRENT_MAX_FILE_SIZE;
char *buffer;

void initializeGlobals();
void debug(char* text);
LexemeList *runScanner(FILE *fin, int verboseOutput);

#endif
