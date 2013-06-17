/*
 * PL0C.c
 *
 *  Created on: Nov 10, 2012
 *      Author: Chris
 */
#include "PL0C.h"

typedef enum {
nulsym = 1, identsym, numbersym, plussym, minussym,
multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
periodsym, becomessym, beginsym, endsym, ifsym, thensym,
whilesym, dosym, callsym, constsym, intsym, procsym, outsym,
insym , elsesym } token_type;

int main ( int argc, char *argv[] ) {
	int i;
	int verboseScanner = 0;
	int verboseParser = 0;
	int verboseVM = 0;
	char* fname;
	char* fcontents;
	LexemeList lex;

	//FILE* fin;
	printf("PL0 Compiler Started!\n");

	for ( i = 1; i < argc; i++ ) {
		printf("Argument: %d - %s\n",i,argv[i]);
		if(argv[i][0] == '-' ) { 		//Option Flag
			switch((int)argv[i][1]) {
				case ((int)'l'): 		// Verbose Scanner - True
					verboseScanner = 1;
					break;
				case((int)'a'):			// Verbose Parser - True
					verboseParser = 1;
					break;
				case((int)'v'):			// Verbose VM - True
					verboseVM = 1;
					break;
				default:				// Unacceptable input. Output Error Message and Terminate!
					printf("Unrecognized Option: %s \nTerminating compilation...\n", argv[i]);
					return 1; 			//Off Nominal Termination
					break;
			}
		}
		else { //If it isn't an option, it should be the last item. I'll go ahead and quit reading in items.
			fname = argv[i];
			break;
		}
	}

	if(fname == NULL) {
		printf("File name was not included!\n");
		exit(1);
	}

	fcontents = extractTextFromFile(fname);
	if (fcontents == NULL) {
		return 1;
	}
	lex = runScanner(fcontents,verboseScanner);

	printf("\nLexeme String \n");
	printLexemeList(lex);
	printf("\n");

	i = runParser(&lex);



	free(fcontents); fcontents = NULL;

	printf("COMPLETE!");
	return 0; 							//Nominal termination
}

/**
 * Print Lexeme List With Symbols
 */
void printLexemeList(LexemeList lex) {
	int i;
	for(i = 0; i < lex.numId; i++) {
		if(lex.list[i] == identsym) {
			printf("%d %s ", lex.list[i++],lex.symbols[lex.list[i+1]]);
		}
		else if(lex.list[i] == numbersym) {
			printf("%d %d ", lex.list[i++], lex.list[i]);
		}
		else {
			printf("%d ", lex.list[i]);
		}
//		if( i % 25 == 0 && i != 0) printf("\n");
	}
//	printf("\n");
//	for(i = 0; i < lex.numId; i++) {
//		printf("%d ", lex.list[i]);
//	}
//	printf("\n");
//	for(i = 0; i < lex.size; i++) {
//		printf("%s ", lex.symbols[i]);
//	}
}

/**
 * Dynamically extracts text from a file. Must remember to free memory afterwards.
 */
char* extractTextFromFile(char* fname) {
	char c;
	int bufferSize = 1024;
	int strSize = 0;
	FILE* fin = fopen(fname, "rb");
	if(fin == NULL) {
		printf("File not available. Check to make sure file exists!\n");
		return NULL;
	}
	char* buffer = (char *)malloc(bufferSize * sizeof(char));


	while((c = fgetc(fin)) != EOF) {
		if(strSize == bufferSize) {
			buffer = (char *)realloc(buffer, 2 * bufferSize*sizeof(char));
			bufferSize *= 2;
		}
		if(buffer == NULL) {
			printf("Memory Allocation Error in function extractTextFromFile!\n");
			return NULL;
		}
		buffer[strSize++] = c;
		if(strSize > 1024){
			printf("BIG ERROR!");
			break;
		}
	}
	buffer[strSize] = '\0'; //insurance
	fclose(fin);
	return buffer;

}


