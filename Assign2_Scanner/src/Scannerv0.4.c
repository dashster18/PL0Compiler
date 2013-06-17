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
#include <string.h>
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

// Signifies whether debug statements are on or off.
int debugFlag = 0;

void initializeGlobals();
void debug(char* text);
void runScanner(FILE *fin);

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
    
    runScanner(fin);
    
    free(buffer);
    fclose(fin);
    
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
void runScanner(FILE *fin) {
    long numChars = 0, numLexemes = 0;
    char c, prev;
    int inComment = 0, i, stringBuilderIndex;
    int *tokens;
    char *lexemes[512]; // Assume we will have 512 lexemes originally
    
    // Read in the file character by character
    printf("Source Program:\n");
    while ((c = fgetc(fin)) != EOF) {
        printf("%c", c);
        if (numChars == CURRENT_MAX_FILE_SIZE) {
            buffer = (char *)realloc(buffer, 2 * CURRENT_MAX_FILE_SIZE);
            CURRENT_MAX_FILE_SIZE *= 2;
            
            if (buffer == NULL) {
                printf("Error. Not enough memory to reallocate\n");
                exit(1);
            }
        }
        
        // If c is a whitespace character, and the previous character was a white space, don't do anything. If the previous character was not a whitespace, add a space to distinguish it from other symbols in the file.
        if ( inComment && prev == '*' && c == '/') { // Turn off comment section
        	inComment = 0;
        }
        else if (inComment) { // If comments are on, ignore characters
            prev = c;
            continue;
        }
        else if ( prev == '/' && c == '*' ) { // Turn on comment section
        	inComment = 1;
        	buffer[numChars - 1] = ' ';
            numChars--;     // This line is so we only have one space after comments and not two
        }
        else if (c == ' ' || c == '\t' || c == '\n') { // Clean whitespace
            if (numChars > 0 && buffer[numChars - 1] == ' ') {
                ;
            }
            else {
                buffer[numChars] = ' ';
                numChars++;
            }
        }
        else { // Otherwise, just put the character in the buffer
            buffer[numChars] = c;
            numChars++;
        }
        prev = c;
    }
    
    // Put a null character that the end of the string in order to make it easy to print out
    if (numChars == CURRENT_MAX_FILE_SIZE) {
        buffer = (char *)realloc(buffer, 2 * CURRENT_MAX_FILE_SIZE);
        CURRENT_MAX_FILE_SIZE *= 2;
        
        if (buffer == NULL) {
            printf("Error. Not enough memory to reallocate\n");
            exit(1);
        }
    }
    
    // Note, after this line numChars doesn't index the null-terminating character. It indexes the character prior to that, aka the last character in the string.
    buffer[numChars] = '\0';
    printf("\n\n");
    
    //printf("\n\n%s\n\n", buffer);
    //exit(0);
    
    // Now tokenize the file and produce the lexemes
    i = 0;
    while (i < numChars) {
        c = buffer[i];
        
        // In this condition, you don't know whether the string is a keyword or an identifier, you'll have to figure this out
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) { // If c is a letter
            
            // Create storage for an identifier or keyword with potentially length of 11 + 1 (for \0)
            lexemes[numLexemes] = (char *)malloc(MAX_ID_LENGTH + 1);
            
            // Create the string
            stringBuilderIndex = 0;
            lexemes[numLexemes][stringBuilderIndex++] = c;
            i++;
            while (i < numChars) {
                c = buffer[i];
                if (c == ' ') {
                    break;
                }
                
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
                    lexemes[numLexemes][stringBuilderIndex++] = c;
                }
                else {
                    lexemes[numLexemes][stringBuilderIndex] = '\0';
                    break; // This break should stop the i++ from getting executed and in the outer for-loop you'll have the current c be the symbol (potentially a special symbol) so the outer loop can deal with it.
                }
                
                if (stringBuilderIndex > MAX_ID_LENGTH) {
                    printf("Error: Identifier Name too long.\n");
                    exit(1);
                }
                
                i++;
            }
            
            // End the string with a null-terminating character
            lexemes[numLexemes][stringBuilderIndex] = '\0';
            numLexemes++;
        }
        else if (c >= '0' && c <= '9') { // If c is the start of a digit
            // Create storage for an identifier or keyword with potentially length of 5 + 1 (for \0)
            lexemes[numLexemes] = (char *)malloc(MAX_NUMBER_DIGITS + 1);
            
            // Create the string
            stringBuilderIndex = 0;
            lexemes[numLexemes][stringBuilderIndex++] = c;
            i++;
            while (i < numChars) {
                c = buffer[i];
                if (c == ' ') {
                    break;
                }
                
                if (c >= '0' && c <= '9') {
                    lexemes[numLexemes][stringBuilderIndex++] = c;
                }
                else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    printf("Error: Invalid Symbols.\n");
                    exit(1);
                }
                else {
                    lexemes[numLexemes][stringBuilderIndex] = '\0';
                    break; // This break should stop the i++ from getting executed and in the outer for-loop you'll have the current c be the symbol (potentially a special symbol) so the outer loop can deal with it.
                }
                
                if (stringBuilderIndex > MAX_NUMBER_DIGITS) {
                    printf("Error: Number too long.\n");
                    exit(1);
                }
                
                i++;
            }
            
            // End the string with a null-terminating character
            lexemes[numLexemes][stringBuilderIndex] = '\0';
            numLexemes++;
        }
        else if ( c == ' ') { // If c is a space, start next token
            i++;
        }
        else { // Otherwise, check if it a special symbol
            // Special Symbols: ‘+’, ‘-‘, ‘*’, ‘/’, ‘(‘, ‘)’, ‘=’, ’,’ , ‘.’, ‘ <’, ‘>’,  ‘;’ , ’:’
            switch (c) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '(':
                case ')':
                case ',':
                case '.':
                case ';':
                case '=':
                    lexemes[numLexemes] = (char *)malloc(2);
                    lexemes[numLexemes][0] = c;
                    lexemes[numLexemes][1] = '\0';
                    numLexemes++;
                    break;
                    
                case '<':
                    // Need to check '=' in here for the optional <= symbol and '>' for the <> symbol
                    lexemes[numLexemes] = (char *)malloc(3);
                    lexemes[numLexemes][0] = c;
                    i++;
                    if (i < numChars && ((c = buffer[i]) == '=' || c == '>')) {
                        lexemes[numLexemes][1] = c;
                        lexemes[numLexemes][2] = '\0';
                    }
                    else {
                        lexemes[numLexemes][1] = '\0';
                        numLexemes++;
                        continue; // Don't want to increment i again
                    }
                    
                    numLexemes++;
                    break;
                    
                case '>':
                case ':':
                    // Need to check '=' in here for the >= or := symbols
                    lexemes[numLexemes] = (char *)malloc(3);
                    lexemes[numLexemes][0] = c;
                    i++;
                    if (i < numChars && (c = buffer[i]) == '=') {
                        lexemes[numLexemes][1] = c;
                        lexemes[numLexemes][2] = '\0';
                    }
                    else {
                        lexemes[numLexemes][1] = '\0';
                        numLexemes++;
                        continue; // Don't want to increment i again
                    }
                    
                    numLexemes++;
                    break;
                    
                default:
                    printf("%c", c);
                    printf("Error: Invalid Symbols.\n");
                    exit(1);
                    break;
            }
            i++;
        }
    }
    
    // Convert into tokens
    tokens = (int *)malloc(numLexemes);
    for (i = 0; i < numLexemes; i++) {
        // Check to see whether it is a symbol, number or special symbol
        c = lexemes[i][0];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            // Need to check whether it is a keyword or an identifier
            if (!strcmp(lexemes[i], "const")) {
                tokens[i] = constsym;
            }
            else if (!strcmp(lexemes[i], "int")) {
                tokens[i] = intsym;
            }
            else if (!strcmp(lexemes[i], "procedure")) {
                tokens[i] = procsym;
            }
            else if (!strcmp(lexemes[i], "call")) {
                tokens[i] = callsym;
            }
            else if (!strcmp(lexemes[i], "begin")) {
                tokens[i] = beginsym;
            }
            else if (!strcmp(lexemes[i], "end")) {
                tokens[i] = endsym;
            }
            else if (!strcmp(lexemes[i], "if")) {
                tokens[i] = ifsym;
            }
            else if (!strcmp(lexemes[i], "then")) {
                tokens[i] = thensym;
            }
            else if (!strcmp(lexemes[i], "else")) {
                tokens[i] = elsesym;
            }
            else if (!strcmp(lexemes[i], "while")) {
                tokens[i] = whilesym;
            }
            else if (!strcmp(lexemes[i], "do")) {
                tokens[i] = dosym;
            }
            else if (!strcmp(lexemes[i], "in")) {
                tokens[i] = insym;
            }
            else if (!strcmp(lexemes[i], "out")) {
                tokens[i] = outsym;
            }
            else {
                // Otherwise it must be an identifier
                tokens[i] = identsym;
            }
        }
        else if (c >= '0' && c <= '9') {
            // Need to convert into an int.
            tokens[i] = numbersym;
        }
        else {
            // Need to convert into the correct symbol code
            if (c != '<' && c != ':' && c != '>') {
                tokens[i] = ssym[c];
            }
            else {
                if (lexemes[i][1] == '=') {
                    switch (c) {
                        case '<':
                            tokens[i] = leqsym;
                            break;
                        case '>':
                            tokens[i] = geqsym;
                            break;
                        case ':':
                            tokens[i] = becomessym;
                            break;
                    }
                }
                else if (c == '<' && lexemes[i][1] == '>') {
                    tokens[i] = neqsym;
                }
            }
        }
    }
    
    // Print lexeme list
    //    printf("Number of Lexemes: %ld\n", numLexemes);
    printf("Lexeme Table:\nlexeme\t\ttoken type\n");
    for (i = 0; i<numLexemes; i++) {
        if (strlen(lexemes[i]) > 7)
            printf("%s\t%d\n", lexemes[i], tokens[i]);
        else if (strlen(lexemes[i]) > 3)
            printf("%s\t\t%d\n", lexemes[i], tokens[i]);
        else
            printf("%s\t\t\t%d\n", lexemes[i], tokens[i]);
    }
    
    // Now print out the final lexeme list
    printf("\nLexeme List:\n");
    for (i = 0; i < numLexemes; i++) {
        printf("%d ", tokens[i]);
        if (tokens[i] == identsym || tokens[i] == numbersym)
            printf("%s ", lexemes[i]);
    }
    
    // Clear all the memory you allocated
    for (i = 0; i < numLexemes; i++) {
        free(lexemes[i]);
    }
    free(lexemes);
    free(tokens);
}

