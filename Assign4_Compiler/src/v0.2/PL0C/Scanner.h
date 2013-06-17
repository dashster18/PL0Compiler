/*
 * Scanner.h
 *
 *  Created on: Nov 10, 2012
 *      Author: Chris
 */

#ifndef SCANNER_H_
#define SCANNER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef NULL
#define NULL   ((void *) 0)
#endif
#define _DEBUG if(verbose)




typedef struct {
	int *list;
    long size;
    long numId;
	char **symbols;
} LexemeList;

void testScannerOut();
LexemeList runScanner(char* fin, int verbose);
LexemeList tokenizeString(char** temp, int verbose);
char** parseTokens(char* str) ;
int isValidNumber(char* str);
int isValidIdent(char* str);



#endif /* SCANNER_H_ */
