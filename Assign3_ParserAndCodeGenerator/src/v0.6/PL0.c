/* Created by Christopher Anderson and Nikesh Srivastava */

#include "Parser.c"
#include "VM.c"

int main(int argc, char **argv){
    
    // Temporary String
    char *foobar = NULL;
    LexemeList *temp = NULL;
    int errorValue = 0, i;
    
    FILE* fn1 = NULL; // Input program
    FILE* fo2 = NULL; // Output program
    FILE* objectFile = NULL;
    
    // No input file. Use default.
    if(argc < 2) {
        fn1 = fopen("P1.in","rb");
        fo2 = fopen("P1.out","wb");
        foobar = "P1.o";
    }
    // Just an input file. Use declared string
    else if(argc == 2) {
        argc--; argv++;
        foobar = *argv;
        fn1 = fopen(foobar, "rb");
        
        argc--; argv++;
        foobar = *argv;
        fo2 = fopen(foobar,"wb");
        
        foobar = "foobar.o";
    }
    // TBD: Flag indicating something special in the run.
    else {
        printf("Error: Too many parameters. Please try again with 2 or less parameters!\n");
        return 1;
    }
    
    // Check for Input File Error
    if(fn1 == NULL) {
        printf("Error: Input file did not open correctly!\n");
        return 1;
    }

    // Run the Scanner first
    temp = runScanner(fn1);
    
    // Then the Parser
    if (temp) {
        errorValue = runParser(temp);
    }
    else {
        // There was an error in the scanner
        exit(1);
    }
    
    // Now convert the code returned from the Parser to code for the Virtual machine
    if (errorValue == 0) {
        objectFile = fopen(foobar, "wb");
        if (objectFile == NULL) {
            printf("Error, could not create intermediate file.\n");
            exit(1);
        }
        
        for (i = 0; i < cx; i++) {
            fprintf(objectFile, "%d %d %d\n", code[i].op, code[i].l, code[i].m);
        }
        
        fclose(objectFile);
        objectFile = fopen(foobar, "rb");
        if (objectFile == NULL) {
            printf("Error, could not create intermediate file.\n");
            exit(1);
        }
    }
    else {
        // There was an error in the parser
        exit(1);
    }
    
    // Then the Virtual Machine
    runPM0(objectFile, fo2);
    
    return 0;
}