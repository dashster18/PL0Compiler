/* Created by Christopher Anderson and Nikesh Srivastava */


#include "Parser.h"
#include "VM.h"

void outputLexemeList(LexemeList *temp, FILE *fo2) {
    int ii;
    if (temp != NULL) {
        printf("Size: %ld\n", temp->size);
        for (ii = 0; ii < temp->size; ii++) {
            printf("%d ", temp->list[ii]);
            if (temp->list[ii] == identsym) {
                ii++;
                if (ii < temp->size)
                    printf("%s ", temp->symbols[temp->list[ii]]);
            }
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
    int ii;
    for (ii = 0; ii < temp->size; ii++) {
        printf("%s ", symbolicRepresentation(temp->list[ii]));
        if (temp->list[ii] == identsym) {
            ii++;
            printf("%s ", temp->symbols[temp->list[ii]]);
        }
        else if (temp->list[ii] == numbersym) {
            ii++;
            printf("%d ", temp->list[ii]);
        }
    }
}

int main(int argc, char **argv){
    //printf("Test 0\n");
    
    // Temporary String
    char *foobar = NULL;
    LexemeList *temp = NULL;
    int errorValue = 0, i;
    
    FILE* fn1 = NULL; // Input program
    FILE* fo2 = NULL; // Output program
    FILE* objectFile = NULL;
    
    //printf("Test 1\n");
    
    // No input file. Use default.
    if(argc < 2) {
        fn1 = fopen("input.pl0","rb");
        //fo2 = fopen("/Users/Nikeshsrivastava/Desktop/Parser/Parser/output","wb");
        //foobar = "/Users/Nikeshsrivastava/Desktop/Parser/Parser/P1.o";
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
    
    //printf("Test 2\n");
    
    // Check for Input File Error
    if(fn1 == NULL) {
        printf("Error: Input file did not open correctly!\n");
        return 1;
    }
    
    
    
    //printf("Test 3\n");
    
    // Run the Scanner first
    temp = runScanner(fn1);
    
    //printf("Test 4\n");
    if (temp == NULL) {
        //printf("Lex list is null\n");
        return 1;
    }
    
    // Now we need to print out the Lexeme List
    // Then run the Parser
    if (temp != NULL) {
        //        outputLexemeList(temp, fo2);      // Instead of being printed out here, Lexeme list is printed in runScanner()
        //printf("\n\n");
        outputSymbolicList(temp, fo2);
        printf("\n\n");
        //printf("Test 5\n");
        errorValue = runParser(temp);
    }
    else {
        // There was an error in the scanner
        exit(1);
    }
    
    //printf("Test 6\n");
    
    // Now convert the code returned from the Parser to code for the Virtual machine
    if (errorValue == 0) {
        printf("No errors, program is syntactically correct\n\n");
        
        printf("Instructions:\n");
        for (i = 0; i < cx; i++) {
            printf("%d %d %d\n", code[i].op, code[i].l, code[i].m);
        }
    }
    else {
        // There was an error in the parser
        // Need to print out program, and then print out the error number
        exit(1);
    }
    
    //printf("Test 7\n");
    
    // Then the Virtual Machine
    printf("\nVirtual Machine:");
    runPM0(objectFile, fo2);
    
    //printf("Test 8\n");
    
    return 0;
}

/* Written by Christopher Anderson and Nikesh Srivastava */

int runParser(LexemeList *LLin){
    LL = LLin;
    ptrLL = 0;
    g_level = 0;
    g_addr = 0;
    if(initSymbolTable() != 0) return 1;
    getNextToken();
    
    if(program() != 0) return 1;
    
    return 0;
}

int initSymbolTable() {
    int i = 0;
    symbolTable = NULL;
    symbolTable = (symbol*) malloc(sizeof(symbol)*(2*LL->numId+1));
    if(symbolTable == NULL) {
        printf("Fatal Error: Malloc returned NULL!");
        return 1;
    }
    
    
    for ( i = 0; i < getTableSize(); i++) {
        symbolTable[i].kind = 0;
    }
    
    return 0;
}

int getTableSize(){
    return (int)(LL->numId*2+1);
}

int hashName(char* ID) {
    int x=0, i = 0;
    int a = getTableSize();
    while(ID[i] != '\0') {
        x += ((int)ID[i] % a);
        i++;
    }
    //printf("Hash Value -> .%s. %d\n",ID,x);
    return x;
}

//Return 1 for fail, 0 for success
int insertConst(char* ID, int val) {
    int hashval = hashName(ID);
    int i = hashval;
    int x = getTableSize();
    do {
        if(symbolTable[hashval].kind == 0)
        {
            symbolTable[hashval].kind = 1;
            symbolTable[hashval].name = ID;
            symbolTable[hashval].val = val;
            return 0;
        }
        else if(!strcmp(ID, symbolTable[hashval].name))
        {
            if(symbolTable[hashval].level == g_level){ return 1; }
        }
        hashval = (hashval+1)%x;
    } while(i != hashval);
    
    return 1;
}



int insertVar(char* ID) {
    int hashval = hashName(ID);
    int i = hashval;
    int x = getTableSize();
    do {
        if(symbolTable[hashval].kind == 0)
        {
            symbolTable[hashval].kind = 1;
            symbolTable[hashval].name = ID;
            symbolTable[hashval].level = g_level;
            symbolTable[hashval].addr = g_addr++;
            return 0;
        }
        else if(!strcmp(ID, symbolTable[hashval].name))
        {
            if(symbolTable[hashval].level == g_level){ return 1; }
        }
        hashval = (hashval+1)%x;
    } while(i != hashval);
    
    return 1;
}

int insertProcedure(char* ID) {
    int hashval = hashName(ID);
    int i = hashval;
    int x = getTableSize();
    do {
        if(symbolTable[hashval].kind == 0)
        {
            symbolTable[hashval].kind = 1;
            symbolTable[hashval].name = ID;
            symbolTable[hashval].level = g_level;
            symbolTable[hashval].addr = g_addr;
            return 0;
        }
        else if(!strcmp(ID, symbolTable[hashval].name))
        {
            if(symbolTable[hashval].level == g_level){ return 1; }
        }
        hashval = (hashval+1)%x;
    } while(i != hashval);
    
    return 1;
}

int fetchIDIndex(char* ID)
{
    //THIS NEEDS TO BE FIXED ONCE WE CAN HAVE NESTED PROCEDURES!!!
    //printf("Num ID -> %ld\n",LL->numId);
    //printf("ID index -> %d\n",(int)(*ID));
    /*    int i;
     for( i = 0; i < 2; i++)
     {
     printf("%d: %s\n",i,LL->symbols[i]);
     }
     */
    int hashval = hashName(LL->symbols[(int)(*ID)]);
    //int i = hashval;
    int x = getTableSize();
    int lastseen = hashval;
    
    //printf("Fetched Hash Value -> %d\n",hashval);
    
    /*    if(symbolTable[hashval].kind == 0) {
     printf("Hash Lookup Failed. ID -> %s\n", ID);
     return -1;
     }
     */
    while(symbolTable[hashval].kind != 0)
    {
        if(strcmp(ID,symbolTable[hashval].name) == 0 ){
            lastseen = hashval;
        }
        hashval = (hashval+1)%x;
    }
    return lastseen;
}

void emit(int op, int l, int m)
{
    if(cx > MAX_CODE_LENGTH)
        error(28);
    else
    {
        code[cx].op = op; 	//opcode
        code[cx].l = l;	// lexicographical level
        code[cx].m = m;	// modifier
        cx++;
    }
}

/*
 1. Use = instead of :=.
 2. = must be followed by a number.
 3. Identifier must be followed by =.
 4. const, int, procedure must be followed by identifier.
 5. Semicolon or comma missing.
 6. Incorrect symbol after procedure declaration.
 7. Statement expected.
 8. Incorrect symbol after statement part in (.
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
 27. No rule
 28. Intermediate code generated too long
 29. Identifier name too long
 */

void error(int errorNum) {
    
    printf("*****Error number %d, ", errorNum);
    switch (errorNum) {
        case 1:
            printf("Use = instead of :=.\n");
            break;
            
        case 2:
            printf("= must be followed by a number.\n");
            break;
            
        case 3:
            printf("Identifier must be followed by =.\n");
            break;
            
        case 4:
            printf("const, int, procedure must be followed by identifier.\n");
            break;
            
        case 5:
            printf("Semicolon or comma missing.\n");
            break;
            
        case 6:
            printf("Incorrect symbol after procedure declaration.\n");
            break;
            
        case 7:
            printf("Statement expected.\n");
            break;
            
        case 8:
            printf("Incorrect symbol after statement part in block.\n");
            break;
            
        case 9:
            printf("Period expected.\n");
            break;
            
        case 10:
            printf("Semicolon between statements missing.\n");
            break;
            
        case 11:
            printf("Undeclared identifier.\n");
            break;
            
        case 12:
            printf("Assignment to constant or procedure is not allowed.\n");
            break;
            
        case 13:
            printf("Assignment operator expected.\n");
            break;
            
        case 14:
            printf("call must be followed by an identifier.\n");
            break;
            
        case 15:
            printf("Call of a constant or variable is meaningless.\n");
            break;
            
        case 16:
            printf("then expected.\n");
            break;
            
        case 17:
            printf("Semicolon or } expected.\n");
            break;
            
        case 18:
            printf("do expected.\n");
            break;
            
        case 19:
            printf("Incorrect symbol following statement.\n");
            break;
            
        case 20:
            printf("Relational operator expected.\n");
            break;
            
        case 21:
            printf("Expression must not contain a procedure identifier.\n");
            break;
            
        case 22:
            printf("Right parenthesis missing.\n");
            break;
            
        case 23:
            printf("The preceding factor cannot begin with this symbol.\n");
            break;
            
        case 24:
            printf("An expression cannot begin with this symbol.\n");
            break;
            
        case 25:
            printf("This number is too large.\n");
            break;
            
        case 26:
            printf(":= expected after Identifier\n");
            break;
            
        case 27:
            //            printf("'end' expected after statement declaration\n");
            break;
            
        case 28:
            printf("Intermediate code generated too long!\n");
            break;
            
        case 29:
            printf("Error: Identifier Name too long.\n");
            break;
    }
}

void getNextToken() {
    token = LL->list[ptrLL++];
    //printf("Token: %d, Index: %d\n", token, ptrLL);
}

char *getID(int index) {
    return LL->symbols[index];
}

/*
 procedure PROGRAM;
 begin
 GET(TOKEN);
 BLOCK;
 if TOKEN != "periodsym" then ERROR
 end;
 */
// Parses syntactic class program, returns error code.
int program() {
    //printf("Program entered\n");
    int errorCode = 0;
    //    getNextToken();
    errorCode = block();
    if (errorCode) return errorCode;    // Propogate error up
    getNextToken();
    if (token != periodsym) {
        error(9);   // period expected
        return 9;
    }
    return 0;
}
/*
 procedure BLOCK;
 begin
 if TOKEN = "constsym" then begin
 repeat
 GET(TOKEN);
 if TOKEN != "identsym" then ERROR;
 GET(TOKEN);
 if TOKEN != "eqsym" then ERROR;
 GET(TOKEN);
 if TOKEN != NUMBER then ERROR;
 GET(TOKEN)
 until TOKEN != "commasym";
 if TOKEN != "semicolomsym" then ERROR;
 GET(TOKEN)
 end;
 if TOKEN = "intsym" then begin
 repeat
 GET(TOKEN);
 if TOKEN != "identsym" then ERROR;
 GET(TOKEN)
 until TOKEN != "commasym";
 if TOKEN != "semicolomsym" then ERROR;
 GET(TOKEN)
 end;
 while TOKEN = "procsym" do begin
 GET(TOKEN);
 if TOKEN != “identsym” then ERROR;
 GET(TOKEN);
 if TOKEN != "semicolomsym" then ERROR;
 GET(TOKEN);
 BLOCK;
 if TOKEN != "semicolomsym" then ERROR;
 GET(TOKEN)
 end;
 STATEMENT
 end;
 */
int block() {
    //printf("Block entered\n");
    int errorCode = 0;
    char *temp = NULL;
    int numVars = 0;
    g_addr = 4;
    emit(inc,0,4);
    if (token == constsym) {
        do {
            getNextToken();
            if (token != identsym) {
                error(4);
                return 4;
            }
            getNextToken();
            temp = getID(token);
            
            getNextToken();
            if (token != eqsym) {
                if (token == becomessym) {
                    error(1);
                    return 1;
                }
                else {
                    error(3);
                    return 3;
                }
            }
            getNextToken();
            if (token != numbersym) {
                error(2);
                return 2;
            }
            getNextToken();
            if (insertConst(temp, token)) {
                return 1;
            }
            
            getNextToken();
        } while (token == commasym);
        
        if (token != semicolonsym) {
            error(5);
            return 5;
        }
        getNextToken();
    }
    if (token == intsym) {
        do {
            getNextToken();
            if (token != identsym) {
                error(4);
                return 4;
            }
            getNextToken();
            if (insertVar(getID(token))) {
                return 1;
            }
            numVars++;
            getNextToken();
        } while (token == commasym);
        
        if (token != semicolonsym) {
            error(5);
            return 5;
        }
        
        // Increment the stack ptr by the number of variables
        emit(inc, 0, numVars);
        getNextToken();
    }
    if (token == procsym) {
        // Throw error because we are not implementing procedure yet
        error(21);
        return 21;
    }
    if (token == periodsym) {
        error(7);
        return 7;
    }
    errorCode = statement();
    if (errorCode) return errorCode;    // Propogate error up
    
    emit(opr,0,0);
    
    
    return 0;
}

/*
 procedure STATEMENT;
 begin
 if TOKEN = "identsym" then begin
 GET(TOKEN);
 if TOKEN != "becomessym" then ERROR;
 GET(TOKEN);
 EXPRESSION
 end
 else if TOKEN = "callsym" then begin
 GET(TOKEN);
 if TOKEN != "identsym" then ERROR;
 GET(TOKEN)
 end
 else if TOKEN = "beginsym" then begin
 GET TOKEN;
 STATEMENT;
 while TOKEN = "semicolomsym" do begin
 GET(TOKEN);
 STATEMENT
 end;
 if TOKEN != "endsym" then ERROR;
 
 GET(TOKEN)
 end
 else if TOKEN = "ifsym" then begin
 GET(TOKEN);
 CONDITION;
 if TOKEN != "thensym" then ERROR;
 GET(TOKEN);
 STATEMENT
 end
 else if TOKEN = "whilesym" then begin
 GET(TOKEN);
 CONDITION;
 if TOKEN != "dosym" then ERROR;
 GET(TOKEN);
 STATEMENT
 end
 end;
 */
int statement() {
    //printf("Statement entered\n");
    int errorCode = 0;
    int temp, start;
    
    switch (token) {
        case identsym:
            getNextToken(); // Get the identifier
            //printf("Token -> %d\n",(int)token);
            temp = fetchIDIndex(&token);
            getNextToken(); // Get token after ident
            if (token != becomessym) {
                error(26);
                return 26;
            }
            getNextToken();
            errorCode = expression();
            if (errorCode) return errorCode;    // Propogate error up
            emit(sto,symbolTable[temp].level,symbolTable[temp].addr);
            break;
            
        case callsym:
            error(21);
            return 21; // Procedure encountered. Illegal.
            /*
             getNextToken();
             if (token != identsym) {
             error(14);
             return 14;
             }
             getNextToken();
             */
            break;
            
        case beginsym: //No code generation needed
            getNextToken();
            errorCode = statement();
            if (errorCode) return errorCode;    // Propogate error up
            while (token == semicolonsym) {
                getNextToken();
                errorCode = statement();
                if (errorCode) return errorCode;    // Propogate error up
                if (token != endsym && token != semicolonsym) {
                    error(10);
                    return 10;
                }
            }
            if (token != endsym) {
                error(5);
                return 5;
            }
            break;
            
        case ifsym: //
            getNextToken();
            errorCode = condition();
            if (errorCode) return errorCode;    // Propogate error up
            if (token != thensym) {
                error(16);
                return 16;
            }
            getNextToken();
			emit(jpc,0,cx+2);
			temp = cx;
			emit(jmp, 0, 0);
            errorCode = statement();
            if (errorCode) return errorCode;    // Propogate error up
            code[temp].m = cx;
			break;
            
        case whilesym:
            getNextToken();
			start = cx;
            errorCode = condition();
            if (errorCode) return errorCode;    // Propogate error up
            emit(jpc, 0, cx+2);
			temp = cx;
			emit(jmp, 0, 0);
			if (token != dosym) {
                error(18);
                return 18;
            }
            getNextToken();
            errorCode = statement();
            if (errorCode) return errorCode;    // Propogate error up
            emit(jmp, 0, start);
			code[temp].m = cx;
			break;
            
        default:
            return 0;
            break;
    }
    
    return 0;
}

/*
 procedure CONDITION;
 begin
 if TOKEN = "oddsym" then begin
 GET(TOKEN);
 EXPRESSION
 else begin
 EXPRESSION;
 if TOKEN != RELATION then ERROR;
 GET(TOKEN);
 EXPRESSION
 end
 end;
 */
int condition() {
    //printf("Condition entered\n");
    int errorCode = 0;
	int temp;
    
    if (token == oddsym) {
        getNextToken();
        errorCode = expression();
        if (errorCode) return errorCode;    // Propogate error up
		emit(opr, 0, 6);
	}
    else {
        errorCode = expression();
        if (errorCode) return errorCode;    // Propogate error up
        if (!(token >= eqsym && token <= geqsym)) { // oddsym, eqsym, neqsym, lessym, leqsym, gtrsym, geqsym. They are in sequential order in the enum.
            error(20);
            return 20;
        }
		temp = token;
        getNextToken();
        errorCode = expression();
        if (errorCode) return errorCode;    // Propogate error up
		emit(opr, 0, 8 + temp - eqsym);	//Since they're in order, we're in luck
    }
    
    return 0;
}

/*
 procedure EXPRESSION;
 begin
 if TOKEN = "plussym"or "minussym" then GET(TOKEN);
 TERM;
 while TOKEN = "plussym" or "minussym" do begin
 GET(TOKEN);
 TERM
 end
 end;
 */
int expression() {
    //printf("Expression entered\n");
    int errorCode = 0;
	int temp;
    /*
     if (token == identsym) {
     getNextToken();
     temp = fetchIDIndex(&token);
     getNextToken();
     
     emit(lod,symbolTable[temp].level,symbolTable[temp].addr);
     }
     else if (token  == numbersym) {
     getNextToken();
     emit(lit,0,token);
     getNextToken();
     }
     */
    
    if (token == plussym || token == minussym) {
        temp = token;
		getNextToken();
    }
    else if (token >= nulsym && token <= elsesym && token != identsym && token != numbersym && token != lparentsym) {
        //error(24);
        //return 24;
    }
    
    errorCode = term();
    
    if(temp == minussym) emit(opr,0,1); //Negate if needs negating
    if (errorCode) return errorCode;    // If there was an error in term, propogate that error up
    
    while (token == plussym || token == minussym) {
        temp = token;
        getNextToken();
        errorCode = term();
        if(temp == plussym)
        {
            //printf("Adding\n");
            emit(opr,0,2); //Plus
        }
        else
        {
            ///printf("Subtracting\n");
            emit(opr,0,3); //Minus
        }
        if (errorCode) return errorCode;    // If there was an error in term, propogate that error up
    }
    
    
    return 0;
}

/*
 procedure TERM;
 begin
 FACTOR;
 while TOKEN = "multsym" or "slashsym" do begin
 GET(TOKEN);
 FACTOR
 end
 end;
 */
int term() {
    //printf("Term entered\n");
    int errorCode = factor(); // Call factor
	int temp;
    if (errorCode) {
        return 1;   // If there was an error in factor, propogate it up
    }
    
    while (token == multsym || token == slashsym) {
        temp = token;
		getNextToken();
        errorCode = factor(); // Call factor
		if(temp == multsym)
		{
			emit(opr, 0, 4);
		}
		else
		{
			emit(opr, 0, 5);
		}
        if (errorCode) return errorCode;   // If there was an error in factor, propogate it up
    }
    
    return 0;
}

/*
 procedure FACTOR;
 begin
 if TOKEN = "identsym then
 GET(TOKEN)
 else if TOKEN = NUMBER then
 GET(TOKEN)
 else if TOKEN = "(" then begin
 GET(TOKEN);
 EXPRESSION;
 if TOKEN != ")" then ERROR;
 GET(TOKEN)
 end
 else ERROR
 end;
 */
int factor() {
    //printf("Factor entered\n");
    int errorCode = 0;
	int temp;
    
    switch (token) {
        case identsym:
			getNextToken();
            //printf("Token -> %d\n",(int)token);
			temp = fetchIDIndex(&token);
            //printf("Fetched: Index -> %d. Symbol - > %s. M -> %d. L -> %d\n",temp, symbolTable[temp].name,symbolTable[temp].addr,symbolTable[temp].level);
			emit(lod, symbolTable[temp].level,symbolTable[temp].addr);
            getNextToken();
            break;
            
        case numbersym:
            getNextToken(); // Get the number after the numbersym
			emit(lit,0,token);
            getNextToken(); // Now get the token after
            break;
            
        case lparentsym: //No code generation needed (yay stacks!)
            getNextToken();
            errorCode = expression();
            if (errorCode) return errorCode;    // Propogate error up
            if (token != rparentsym) {
                error(22);
                return 22;
            }
            getNextToken();
            break;
            
        default:
            error(23);   // Not sure what error to put here
            return 23;
            break;
    }
    return 0;
}

void runPM0(FILE* fn1, FILE* fo2) {
    //void runPM0(FILE* fn1) {
    // When running the VM, make a stack and an instruction array
    int stack[MAX_STACK_HEIGHT];
    //instructionData code[MAX_CODE_LENGTH];
    regFile registers;
    int instructionCount = 0, i;
    
    // Initialize registers
    registers.SP = 0;
    registers.BP = 1;
    registers.PC = 0;
    registers.IR.op = 0;
    registers.IR.l = 0;
    registers.IR.m = 0;
    
    // Initialize stack
    for(i = 0; i < MAX_STACK_HEIGHT; i++) {
        stack[i] = 0;
    }
    
    
    // Read in the instructions into the instruction array
    /*
     while (fscanf(fn1, "%d%d%d ", &code[instructionCount].op, &code[instructionCount].l, &code[instructionCount].m) != EOF) {
     // Increment the instructionIterator
     instructionCount++;
     }
     */
    
    // Now that we have the instructions, we can now start the execution of the program.
    //printf("Line  OP   L   M\n");
    
    // Print out the instructions in assembly language format
    for(i = 0; i < instructionCount; i++) {
        printf(" %3d %3s %3d %3d\n", i, OPCODES[code[i].op], code[i].l, code[i].m);
    }
    
    printf("\n");
    printf("Line  OP   L   M  pc  bp  sp  stack\n");
    printf("  Initial Values   0   1   0  -EMPTY-\n");
    
    // Now we need to do the fetch and execute cycles for all the instructions
    //for(i = 0; i < instructionCount; i++) {
    while(registers.BP > 0) { //CJA - TBD - Changed this because we don't go for "instruction count" times. We go until the base pointer is dead. ( THIS NEEDS TO BE CONFIRMED! )
        // Fetch: (Since it is one line of code, I decided not to write a function for it)
        //  IR <- code[PC]
        //  PC <- PC + 1
        registers.IR = code[registers.PC++];
        printf(" %3d %3s %3d %3d", registers.PC-1, OPCODES[code[registers.PC-1].op], code[registers.PC-1].l, code[registers.PC-1].m);
        // Execute:
        execute(fo2, code, stack, &registers);
        //execute(code, stack, &registers);
        printf(" %3d %3d %3d ", registers.PC, registers.BP, registers.SP);
        //for(j = 0; j <= registers.SP; j++) {
        //            printf(" %d", stack[j]);
        //        }
        //        printf("\n");
        printStack(stack, registers, fo2);
        printf("\n");
    }
}

// This is the execute cycle in the P-machine cycles.
//  fout: the file pointer to where output is printed
//  code: The code of the program currently being executed
//  stack: The stack for the current runtime environment
//  registers: Data structure containing all the registers of the CPU, reason for being a pointer is
//             because we want changes to be carried back to our runPM0 function.
void execute(FILE *fo2, instruction code[], int stack[], regFile *registers) {
    //void execute(instruction code[], int stack[], regFile *registers) {
    // Use the op-code to figure out what instruction you will execute
    // instruction is stored in registers->IR
    
    // LIT 0, M
    //  Push a literal M onto the top of the stack
    if (registers->IR.op == 1) {
        registers->SP = registers->SP + 1;
        stack[registers->SP] = registers->IR.m;
    }
    // OPR 0, M
    //  Operation to be performed on the data at the top of the stack
    else if (registers->IR.op == 2) {
        // Execute the instruction that is signified by the M value
        
        // RET
        if (registers->IR.m == 0) {
            registers->SP = registers->BP - 1;
            registers->PC = stack[registers->SP + 4];
            registers->BP = stack[registers->SP + 3];
        }
        // NEG
        else if (registers->IR.m == 1) {
            // No idea what you're supposed to do with -stack[sp]
            // Not sure if this is correct
            stack[registers->SP] = -1 * stack[registers->SP];
        }
        // ADD
        else if (registers->IR.m == 2) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] + stack[registers->SP + 1];
        }
        // SUB
        else if (registers->IR.m == 3) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] - stack[registers->SP + 1];
        }
        // MUL
        else if (registers->IR.m == 4) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] * stack[registers->SP + 1];
        }
        // DIV
        else if (registers->IR.m == 5) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] / stack[registers->SP + 1];
        }
        // ODD
        else if (registers->IR.m == 6) {
            // Mistake in document, please verify
            stack[registers->SP] = stack[registers->SP] % 2;
        }
        // MOD
        else if (registers->IR.m == 7) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] % stack[registers->SP + 1];
        }
        // EQL
        else if (registers->IR.m == 8) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] == stack[registers->SP + 1];
        }
        // NEQ
        else if (registers->IR.m == 9) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] != stack[registers->SP + 1];
        }
        // LSS
        else if (registers->IR.m == 10) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] < stack[registers->SP + 1];
        }
        // LEQ
        else if (registers->IR.m == 11) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] <= stack[registers->SP + 1];
        }
        // GTR
        else if (registers->IR.m == 12) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] > stack[registers->SP + 1];
        }
        // GEQ
        else if (registers->IR.m == 13) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] >= stack[registers->SP + 1];
        }
    }
    // LOD L, M
    //  Load value to top of stack from the stack location at offset M from L lexicographical levels down
    else if (registers->IR.op == 3) {
        registers->SP = registers->SP + 1;
        stack[registers->SP] = stack[base(registers->IR.l, registers->BP, stack) + registers->IR.m];
    }
    // STO L, M
    //  Store value at top of stack in the stack location at offset M from L lexicographical levels down
    else if (registers->IR.op == 4) {
        stack[base(registers->IR.l, registers->BP, stack) + registers->IR.m] = stack[registers->SP];
        registers->SP = registers->SP - 1;
    }
    // CAL L, M
    //  Call procedure at code index M (generates new Activation Record and pc <- M)
    else if (registers->IR.op == 5) {
        stack[registers->SP + 1] = 0;               // Spot for functional return value
        stack[registers->SP + 2] = base(registers->IR.l, registers->BP, stack);        // Static Link
        stack[registers->SP + 3] = registers->BP;   // Dynamic Link
        stack[registers->SP + 4] = registers->PC;   // Return Address
        registers->BP = registers->SP + 1;
        registers->PC = registers->IR.m;
    }
    // INC 0, M
    //  Allocate M locals (increment SP by M). First three are Static Link (SL), Dynamic Link (DL), and Return Address (RA)
    else if (registers->IR.op == 6) {
        registers->SP = registers->SP + registers->IR.m;
    }
    // JMP 0, M
    //  Jump to instruction M
    else if (registers->IR.op == 7) {
        registers->PC = registers->IR.m;
    }
    // JPC 0, M
    //  Jump to instruction M if top stack element is 0
    else if (registers->IR.op == 8) {
        if (stack[registers->SP] != 0) {
            registers->PC = registers->IR.m;
        }
        registers->SP = registers->SP - 1;
    }
    // SIO 0, 1
    //  Write the top of the stack element to the screen
    else if (registers->IR.op == 9) {
        printf("%d", stack[registers->SP]);
        registers->SP = registers->SP - 1;
    }
    // SIO 0, 2
    //  Read an input from the user and store it at the top of the stack
    else if (registers->IR.op == 10) {
        registers->SP = registers->SP + 1;
        scanf("%d", &stack[registers->SP]);
    }
    // Instruction Input error, this instruction is not in the ISA
    else {
        
    }
}

/**********************************************/
/*		Find base L levels down               */
/*                                            */
/**********************************************/
int base(int l, int base, int stack[]) // l stand for L in the instruction format
{
    int b1; //find base L levels down
    b1 = base;
    
    while (l > 0) {
        //CJA - Changed this to b1+1 from just b1. You need the Static Link,
        //      not the return value.
        b1 = stack[b1+1];
        l--;
    }
    //printf("\nbase returns: %d\n",b1);
    return b1;
}

/******************************************/
/*     Print Stack              ***********/
/*****************************************/
void printStack(int stack[], regFile registers, FILE* fo2) {
    //    int mSP = registers.SP;
    int mBP = registers.BP;
    int mDL = stack[mBP + 2];
    
    int buffer[5008];
    int j = 0;
    int i = registers.SP+1;
    int max = 1;
    //printf("i: %d\n",i);
    //printf("mBP: %d\n",mBP);
    //printf("mDL: %d\n",mDL);
    
    //if( i < mBP && mBP != 1) mBP = mDL;
    for(j = 0; j < registers.SP+1; j++) {
        if(stack[j] > max) max = stack[j];
    }
    j = 0;
    
    if (registers.IR.op == 5) {
        buffer[j++] = stack[i+4];
        buffer[j++] = stack[i+3];
        buffer[j++] = stack[i+2];
        buffer[j++] = stack[i+1];
    }
    
    while (i > 1){
        //printf("i: %d BP: %d DL: %d\n",i,mBP,mDL);
        if( mBP <= 1) {
            buffer[j++] = stack[i];
            i--;
        }
        else {
            while(i > 1 && i >= mBP) {
                buffer[j++] = stack[i];
                i--;
            }
            buffer[j++] = 0x80000000;
            mBP = mDL;
            mDL = stack[mBP + 2];
            if(mBP > registers.BP) getchar();
        }
    }
    //buffer[j] = '\0';
    if(j == 0) printf(" -EMPTY- ");
    if(max < 100){
        for(j = j; j > 0; j--) {
            if(buffer[j] == 0x80000000) {
                printf("  |");
            }
            else {
                printf(" %2d", buffer[j]);
            }
        }
    }
    else if(max < 1000) {
        for(j = j; j > 0; j--) {
            if(buffer[j] == 0x80000000) {
                printf("   |");
            }
            else {
                printf(" %3d", buffer[j]);
            }
        }
    }
    else {// if(max < 10000) {
        for(j = j; j > 0; j--) {
            if(buffer[j] == 0x80000000) {
                printf("    |");
            }
            else {
                printf(" %4d", buffer[j]);
            }
        }
    }
    
} //End of printStack

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
    buffer = (char *)malloc(INITIAL_MAX_FILE_SIZE * sizeof(char));
}


int getIndex(char **strs, char *str, int *index) {
    int i;
    
    for (i = 0; i < *index; i++) {
        if (strcmp(strs[i], str) == 0) {
            //printf("Index Found!: %s -> %d\n", str, i);
            return i;
        }
    }
    
    //printf("New Index needed: %s -> %d\n", str, (*index));
    (*index)++;
    return (*index) - 1;
}

// Starts the execution of the Lexical Analyzer
LexemeList *runScanner(FILE *fin) {
    // Initialize
    initializeGlobals();
    
    long numChars = 0, numLexemes = 0, numIdents = 0, numIDandNumbers = 0;
    char c, prev;
    int inComment = 0, i, stringBuilderIndex, lexIndex, symbolIndex, tailIndex = 0;
    int *tokens;
    char *lexemes[512]; // Assume we will have 512 lexemes originally
    LexemeList *LexList = NULL;
    
    // Read in the file character by character
    printf("Source Program:\n");
    while ((c = fgetc(fin)) != EOF) {
        printf("%c", c);
        if (numChars == CURRENT_MAX_FILE_SIZE) {
            buffer = (char *)realloc(buffer, 2 * CURRENT_MAX_FILE_SIZE*sizeof(char));
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
        else if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v') { // Clean whitespace
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
        buffer = (char *)realloc(buffer, 2 * CURRENT_MAX_FILE_SIZE * sizeof(char));
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
            lexemes[numLexemes] = (char *)malloc((MAX_ID_LENGTH + 1) * sizeof(char));
            
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
                    error(29);  // Id name too long
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
            lexemes[numLexemes] = (char *)malloc((MAX_NUMBER_DIGITS + 1) * sizeof(char));
            
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
                    error(25);  // Number too long
                    return NULL;
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
                    lexemes[numLexemes] = (char *)malloc(2 * sizeof(char));
                    lexemes[numLexemes][0] = c;
                    lexemes[numLexemes][1] = '\0';
                    numLexemes++;
                    break;
                    
                case '<':
                    // Need to check '=' in here for the optional <= symbol and '>' for the <> symbol
                    lexemes[numLexemes] = (char *)malloc(3 * sizeof(char));
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
                    lexemes[numLexemes] = (char *)malloc(3 * sizeof(char));
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
    tokens = (int *)malloc(numLexemes * sizeof(int));
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
            else if (!strcmp(lexemes[i], "odd")) {
                tokens[i] = oddsym;
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
                else if (c == '<') {
                    tokens[i] = lessym;
                }
                else if (c == '>') {
                    tokens[i] = gtrsym;
                }
            }
        }
    }
    
    // Print lexeme list
    //    printf("Number of Lexemes: %ld\n", numLexemes);
    /*    printf("Lexeme Table:\nlexeme\t\ttoken type\n");
     for (i = 0; i<numLexemes; i++) {
     if (strlen(lexemes[i]) > 7)
     printf("%s\t%d\n", lexemes[i], tokens[i]);
     else if (strlen(lexemes[i]) > 3)
     printf("%s\t\t%d\n", lexemes[i], tokens[i]);
     else
     printf("%s\t\t\t%d\n", lexemes[i], tokens[i]);
     }
     */
    // Now print out the final lexeme list
    printf("Lexeme List:\n");
    for (i = 0; i < numLexemes; i++) {
        printf("%d ", tokens[i]);
        if (tokens[i] == identsym || tokens[i] == numbersym) {
            printf("%s ", lexemes[i]);
            numIDandNumbers++;
            if (tokens[i] == identsym)
                numIdents++;
        }
    }
    printf("\n\n");
    
    // Create the lexeme list
    LexList = malloc(sizeof(LexemeList));
    if (!LexList) {
        printf("Fatal Error. Cannot allocate memory for lexeme list.");
        exit(1);
    }
    LexList->list = malloc(sizeof(int) * (numLexemes + numIDandNumbers));
    LexList->symbols = malloc(sizeof(char) * numIdents);
    if (!LexList->list || !LexList->symbols) {
        printf("Fatal Error. Cannot allocate memory for lexeme list.");
        exit(1);
    }
    
    for (i = 0, lexIndex = 0, symbolIndex = 0, tailIndex = 0; i < numLexemes; i++, lexIndex++) {
        LexList->list[lexIndex] = tokens[i];
        if (tokens[i] == identsym) {
            lexIndex++;
            symbolIndex = getIndex(LexList->symbols, lexemes[i], &tailIndex);
            LexList->list[lexIndex] = symbolIndex;
            LexList->symbols[symbolIndex] = malloc(sizeof(char) * strlen(lexemes[i]));
            if (!LexList->symbols[symbolIndex]) {
                printf("Fatal Error. Cannot allocate memory for lexeme list.");
                exit(1);
            }
            LexList->symbols[symbolIndex] = strcpy(LexList->symbols[symbolIndex], lexemes[i]);
        }
        else if (tokens[i] == numbersym) {
            lexIndex++;
            LexList->list[lexIndex] = atoi(lexemes[i]);
        }
    }
    
    LexList->size = numLexemes + numIDandNumbers;
    LexList->numId = numIdents;
    
    // Clear all the memory you allocated
    for (i = 0; i < numLexemes; i++) {
        free(lexemes[i]);
    }
    free(tokens);
    
    return LexList;
}
