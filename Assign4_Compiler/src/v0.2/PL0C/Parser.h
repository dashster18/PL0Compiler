/*
 * Parser.h
 *
 *  Created on: Nov 11, 2012
 *      Author: Chris
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"

#define MAX_SYMBOL_TABLE_SIZE 97 // Not sure what to make this, so I just made it a prime
#define MAX_CODE_LENGTH 500



// Struct for symbol table
typedef struct {
	int kind; 		// const = 1, int = 2, proc = 3
	char *name;	// name up to 11 chars
	int val; 		// number (ASCII value)
	int level; 		// L level
	int addr; 		// M address
} symbol;

//typedef struct {
//	int *list;
//    long size;
//    long numId;
//	char **symbols;
//} LexemeList;

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

#endif /* PARSER_H_ */
