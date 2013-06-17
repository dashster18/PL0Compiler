/* Created by Christopher Anderson and Nikesh Srivastava */

#include "Parser.c"
#include "VM.c"

void outputLexemeList(LexemeList *temp, FILE *fo2) {
    long ii;
    for (ii = 0; ii < temp->size; ii++) {
        fprintf(fo2, "%d ", temp->list[ii]);
        if (temp->list[ii] == identsym) {
            ii++;
            fprintf(fo2, "%s ", temp->symbols[temp->list[ii]]);
        }
    }
}

char *symbolicRepresentation(token_type input) {
    switch (input) {
        case nulsym:
            return "nulsym";
            break;
            
        case identsym:
            return "identsym";
            break;
            
        case numbersym:
            return "numbersym";
            break;
            
        case plussym:
            return "plussym";
            break;
            
        case minussym:
            return "minusym";
            break;
            
        case multsym:
            return "multsym";
            break;
            
        case slashsym:
            return "slashsym";
            break;
            
        case oddsym:
            return "oddsym";
            break;
            
        case eqsym:
            return "eqsym";
            break;
            
        case neqsym:
            return "neqsym";
            break;
            
        case lessym:
            return "lessym";
            break;
            
        case leqsym:
            return "leqsym";
            break;
            
        case gtrsym:
            return "gtrsym";
            break;
            
        case geqsym:
            return "geqsym";
            break;
            
        case lparentsym:
            return "lparentsym";
            break;
            
        case rparentsym:
            return "rparentsym";
            break;
            
        case commasym:
            return "commasym";
            break;
            
        case semicolonsym:
            return "semicolonsym";
            break;
            
        case periodsym:
            return "periodsym";
            break;
            
        case becomessym:
            return "becomessym";
            break;
            
        case beginsym:
            return "beginsym";
            break;
            
        case endsym:
            return "endsym";
            break;
            
        case ifsym:
            return "ifsym";
            break;
            
        case thensym:
            return "thensym";
            break;
            
        case whilesym:
            return "whilesym";
            break;
            
        case dosym:
            return "dosym";
            break;
            
        case callsym:
            return "callsym";
            break;
            
        case constsym:
            return "constsym";
            break;
            
        case intsym:
            return "intsym";
            break;
            
        case procsym:
            return "procsym";
            break;
            
        case outsym:
            return "outsym";
            break;
            
        case insym:
            return "insym";
            break;
            
        case elsesym:
            return "elsesym";
            break;
            
        default:
            break;
    }
}

void outputSymbolicList(LexemeList *temp, FILE *fo2) {
    long ii;
    for (ii = 0; ii < temp->size; ii++) {
        fprintf(fo2, "%s ", symbolicRepresentation(temp->list[ii]));
        if (temp->list[ii] == identsym) {
            ii++;
            fprintf(fo2, "%s ", temp->symbols[temp->list[ii]]);
        }
        else if (temp->list[ii] == numbersym) {
            ii++;
            fprintf(fo2, "%d ", temp->list[ii]);
        }
    }
}

int main(int argc, char **argv){
    
    // Temporary String
    char *foobar = NULL;
    LexemeList *temp = NULL;
    int errorValue = 0, i;
    long ii;
    
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
    
    // Now we need to print out the Lexeme List
    // Then run the Parser
    if (temp) {
        outputLexemeList(temp, fo2);
        fprintf(fo2, "\n\n");
        outputSymbolicList(temp, fo2);
        fprintf(fo2, "\n\n");
        
        errorValue = runParser(temp);
    }
    else {
        // There was an error in the scanner
        exit(1);
    }
    
    // Now convert the code returned from the Parser to code for the Virtual machine
    if (errorValue == 0) {
        fprintf(fo2, "No errors, program is syntactically correct\n\n");
        
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
        // Need to print out program, and then print out the error number
        exit(1);
    }
    
    // Then the Virtual Machine
    runPM0(objectFile, fo2);
    
    return 0;
}