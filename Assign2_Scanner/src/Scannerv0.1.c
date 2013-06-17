/* Written By: Nikesh Srivatava & Chris Anderson
 * ---- Version Table ----
 * |==============================================================|
 * | Ver   | Dates      | Author   | Comments                     |
 * |=======|============|==========|==============================|
 * | v0.1  | 2012.10.03 | Nikesh   | Original Code                |
 * |==============================================================|
 */

// REGULAR EXPRESSIONS:
// Identifiers: identsym = letter (letter | digit)*
// Numbers: numbersym = (digit)+

#include <stdio.h>
#include <stdlib.h>
#define INITIAL_MAX_FILE_SIZE 1 << 10 // 1024
#define MAX_ID_LENGTH 11
#define MAX_NUMBER_DIGITS 5
#define NUMBER_RESERVED_WORDS 13

typedef enum {
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, intsym, procsym, outsym,
    insym , elsesym
} token_type;

char *word[] = {"const", "int", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "in", "out"};
int wordSymbol[] = {constsym, intsym, procsym, callsym, beginsym, endsym, ifsym, thensym, elsesym, whilesym, dosym, insym, outsym};
int ssym[256];
int CURRENT_MAX_FILE_SIZE;
char *buffer;
char *errors[] = {"Variable does not start with a letter", "Number too long", "Name too long", "Invalid symbols"};

// Signifies whether debug statements are on or off.
int debugFlag = 0;

void initializeGlobals();
void debug(char* text);
void runScanner(FILE *fin, FILE *fout);

int main(int argc, char * argv[])
{
    // Initialize
    initializeGlobals();
    
    // Temporary String
    char *foobar;
    
    FILE* fin; // Input
    FILE* fout; // Output
    
    // No input file. Use default.
    if(argc < 2) {
        fin = fopen("Scanner.in","rb");
        fout = fopen("Scanner.out","wb");
    }
    // Just an input file. Use declared string
    else if(argc == 2) {
        argc--; argv++;
        foobar = *argv;
        fin = fopen(foobar, "rb");
        
        argc--; argv++;
        foobar = *argv;
        fout = fopen(foobar,"wb");
    }
    // TBD: Flag indicating something special in the run.
    else {
        debug("Error: Parameter Format. Please try again!\n");
        return 1;
    }
    
    // Check for Input File Error
    if(fin == NULL) {
        debug("Error: Input file did not open correctly!\n");
        return 1;
    }
    
    fclose(fin);
    fclose(fout);
    return 0;
}

// Initialize globals
void initializeGlobals() {
    // Initialize ssym with values
    ssym[(int)'+'] = plussym;
	ssym[(int)'-']= minussym;
	ssym[(int)'*'] = multsym;
    ssym[(int)'/'] = slashsym;
    ssym[(int)'('] = lparentsym;
 	ssym[(int)')'] = rparentsym;
    ssym[(int)'='] = eqsym;
    ssym[(int)','] = commasym;
 	ssym[(int)'.'] = periodsym;
    ssym[(int)'#'] = neqsym;
 	ssym[(int)'<'] = lessym;
 	ssym[(int)'>'] = gtrsym;
    ssym[(int)'$'] = leqsym;
 	ssym[(int)'%'] = geqsym;
 	ssym[(int)';'] = semicolonsym;
    
    // Initialize buffer for inputFile
    CURRENT_MAX_FILE_SIZE = INITIAL_MAX_FILE_SIZE;
    buffer = (char *)malloc(INITIAL_MAX_FILE_SIZE);
}

// Prints the string passed in to screen.
void debug(char* text) {
    if(debugFlag) printf("%s",text);
}

// Starts the execution of the Lexical Analyzer
void runScanner(FILE *fin, FILE *fout) {
    long numChars = 0;
    char c;
    
    // Read in the file character by character
    while ((c = fgetc(fin)) != EOF) {
        if (numChars == CURRENT_MAX_FILE_SIZE) {
            buffer = (char *)realloc(buffer, 2 * CURRENT_MAX_FILE_SIZE);
            CURRENT_MAX_FILE_SIZE *= 2;
            
            if (buffer == NULL) {
                printf("Error. Not enough memory to reallocate\n");
                exit(1);
            }
        }
        
        // If c is a whitespace character, and the previous character was a white space, don't do anything. If the previous character was not a whitespace, add a space to distinguish it from other symbols in the file.
        if (c == ' ' || c == '\t' || c == '\n') {
            if (numChars > 0 && buffer[numChars - 1] == ' ') {
                ;
            }
            else {
                buffer[numChars] = ' ';
                numChars++;
            }
        }
        
        // Otherwise, just put the character in the buffer
        else {
            buffer[numChars] = c;
            numChars++;
        }
    }
    
    // Check whether the input file is grammatically correct
    
    
    // Now tokenize the file and produce the lexemes
}

