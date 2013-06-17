/*
 * Scanner.c
 *
 *  Created on: Nov 10, 2012
 *      Author: Chris
 */

#include "Scanner.h"

typedef enum {
nulsym = 1, identsym, numbersym, plussym, minussym,
multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
periodsym, becomessym, beginsym, endsym, ifsym, thensym,
whilesym, dosym, callsym, constsym, intsym, procsym, outsym,
insym , elsesym } token_type;

char someTokens[34][15] = {"blank", "null", "ident", "number", "+", "-", "*", "/",
		"odd", "=", "<>", "<", "<=", ">", ">=", "(", ")", ",", ";",
		".", ":=","begin","end", "if", "then", "while", "do" , "call", "const", "int", "procedure", "write", "read", "else"};

void testScannerOut() {
	printf("Scanner Output Success!\n");
}

/**
 * Run the Scanner portion of the Compiler
 */
LexemeList runScanner(char* fin, int verbose) {
	LexemeList lex;
	char** output;
//	int i = 0;

	if(verbose != 0){
		verbose = 1; //ensure it's a valid 1 value
	}

	_DEBUG printf("Source Program:\n");
	_DEBUG printf("%s",fin);

	output = parseTokens(fin);
	_DEBUG
	{
//		while(output[i][0] != '#') {
//				printf("%d -- %s\n",i,output[i]);
//				i++;
//			}
	}

	lex = tokenizeString(output,verbose);

	return lex;
}
/**
 * Return the LexemeList which contains the tokenized version of the string and the linked symbols
 */
LexemeList tokenizeString(char** temp, int verbose){
	LexemeList lex;
	int i = 1;
	int j = 0;
	int flag;
	int numLex = 1024;
	//Break up the string!

	lex.list = (int *) malloc(2*numLex*sizeof(int));
	lex.numId = 0;
	lex.size = 0;
	lex.symbols = (char **) malloc(numLex*sizeof(char*));
	for(i = 0; i < numLex; i++) {
		lex.symbols[i] = (char*) malloc(15*sizeof(char));
	}
	_DEBUG printf("Lexeme Table:\n");
	_DEBUG printf("lexeme         token type\n");
	for(i = 0; i < numLex; i++) {
		//printf("%d ",i);
		flag = 0;
		if(temp[i][0] == '#') {
			//printf("End found at %d\n",i);
			break;
		}
		for(j = 4; j < 33; j++) {
			if(!strcmp(temp[i],someTokens[j])) {
				lex.list[lex.numId++] = j;
				flag = 1;
				_DEBUG printf("%-15s %d\n",temp[i],j);
				break;
			}
		}
		if(flag) continue;
		if(isValidNumber(temp[i])) {
			lex.list[lex.numId++] = numbersym;
			lex.list[lex.numId++] = atoi(temp[i]);
			_DEBUG printf("%-15s %d\n",temp[i],numbersym);
		}
		else if(isValidIdent(temp[i])) {
			lex.list[lex.numId++] = identsym;
			strcpy(lex.symbols[lex.size],temp[i]);
			lex.list[lex.numId++] = lex.size;
			lex.size++;
			_DEBUG printf("%-15s %d\n",temp[i],identsym);
		}
		else {
			if(i == 0) continue;
			printf("Parsing error! - %d - %s\n", i, temp[i]);
			exit(1);
		}
	}

	return lex;
}

/**
 * Cleans the comments and excess whitespace from the given string
 */
char** parseTokens(char* str) {
	int i, j, curr, index;
	char** list = (char **) malloc (1024*sizeof(char *));
	for(i = 0; i < 1024; i++) {
		list[i] = (char *) malloc(15*sizeof(char));
	}

	i = 0; j = 0; curr = 0; index = 0;

	while(1) {
		if(str[index] == '\0') {
			break;
		}
		if(str[index] == ' ' || str[index] == '\n' || str[index] == '\t' || str[index] == '\v' || str[index] == '\r') {
			index++;
			continue;
		}
		if(str[index] == '/' && str[index+1] == '*') {
			while(1) {
				if(str[index-1] == '*' && str[index] == '/') break;
				index++;
			}
			index++;
			continue;
		}
		if(str[index] == ':' && str[index+1] == '=') {
			list[curr][0] = ':';
			list[curr][1] = '=';
			list[curr][2] = '\0';
			curr++;
			index++; index++;
			continue;
		}
		if(str[index] == '<' && str[index+1] == '=') {
			list[curr][0] = '<';
			list[curr][1] = '=';
			list[curr][2] = '\0';
			curr++;
			index++; index++;
			continue;
		}
		if(str[index] == '>' && str[index+1] == '=') {
			list[curr][0] = '>';
			list[curr][1] = '=';
			list[curr][2] = '\0';
			curr++;
			index++; index++;
			continue;
		}
		if(str[index] == '<' && str[index+1] == '>') {
			list[curr][0] = '<';
			list[curr][1] = '>';
			list[curr][2] = '\0';
			curr++;
			index++; index++;
			continue;
		}
		i = 0;
		list[curr][i] = str[index];
		if(!((str[index] >= 'a' && str[index] <= 'z') || (str[index] >= 'A' && str[index] <= 'Z') || (str[index] >= '0' && str[index] <= '9'))) {
			index++; i++;
			list[curr][i] = '\0';
			curr++;
			continue;
		}
		index++; i++;
		while((str[index] >= 'a' && str[index] <= 'z') || (str[index] >= 'A' && str[index] <= 'Z') || (str[index] >= '0' && str[index] <= '9')) {
			list[curr][i] = str[index];
			i++; index++;
		}
		list[curr][i] = '\0';
		curr++;
	}

	list[curr][0] = '#';
	list[curr][1] = '#';
	list[curr][2] = '#';
	list[curr][3] = '\0';
	return list;
}

int isValidNumber(char* str) {
	if(str == NULL) return -1;
	int i = 0;
	int valid = 1;
	while(str[i] != '\0') {
		if(str[i] < '0' || str[i] > '9') {
			valid = 0;
		}
		i++;
		if(i > 1024){
			printf("BIG ERROR!");
			break;
		}
	}
	if( i > 5 ) {
		valid = 0;
	}
	return valid;
}

int isValidIdent(char* str) {
	if(str == NULL) return -1;
	//printf("TEST -- %s\n",str);
	int i = 0;
	int valid = 1;
	while(str[i] != '\0') {
		//printf("%c",str[i]);
		if(str[i] >= 'a' && str[i] <= 'z') {
			//valid
		}
		else if(str[i] >= 'A' && str[i] <= 'Z') {
			//valid
		}
		else if(str[i] >= '0' && str[i] <= '9') {
			//valid
		}
		else {
			valid = 0;
		}
		i++;
		if(i > 1024){
			printf("BIG ERROR!");
			break;
		}
	}
	if( i > 11 ) {
			valid = 0;
		}
	return valid;
}

