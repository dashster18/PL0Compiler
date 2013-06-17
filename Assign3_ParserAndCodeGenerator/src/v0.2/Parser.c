/* Written by Christopher Anderson and Nikesh Srivastava */

#include "LexicalAnalyzer.c"

int main(int argc, const char * argv[])
{
    
    return 0;
}

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
    while(ID[i] != '\0') {
        x += ((int)ID[i] % getTableSize());
    }
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
    int hashval = hashName(ID);
    int i = hashval;
    int x = getTableSize();
    int lastseen = -1;
    
    if(symbolTable[hashval].kind == 0) return -1;
    while(symbolTable[hashval].kind != 0)
    {
        if(!strcmp(ID,symbolTable[hashval].name) ){
            lastseen = hashval;
        }
        hashval++;
    }
    return lastseen;
}

void emit(int op, int l, int m)
{
    if(cx > MAX_CODE_LENGTH)
        error(25);
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
 8. Incorrect symbol after statement part in block.
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
 */

void error(int errorNum) {
    switch (errorNum) {
        case 1:
            printf("Use = instead of :=.");
            break;
            
        case 2:
            printf("= must be followed by a number.");
            break;
            
        case 3:
            printf("Identifier must be followed by =.");
            break;
            
        case 4:
            printf("const, int, procedure must be followed by identifier.");
            break;
            
        case 5:
            printf("Semicolon or comma missing.");
            break;
            
        case 6:
            printf("Incorrect symbol after procedure declaration.");
            break;
            
        case 7:
            printf("Statement expected.");
            break;
            
        case 8:
            printf("Incorrect symbol after statement part in block.");
            break;
            
        case 9:
            printf("Period expected.");
            break;
            
        case 10:
            printf("Semicolon between statements missing.");
            break;
            
        case 11:
            printf("Undeclared identifier.");
            break;
            
        case 12:
            printf("Assignment to constant or procedure is not allowed.");
            break;
            
        case 13:
            printf("Assignment operator expected.");
            break;
            
        case 14:
            printf("call must be followed by an identifier.");
            break;
            
        case 15:
            printf("Call of a constant or variable is meaningless.");
            break;
            
        case 16:
            printf("then expected.");
            break;
            
        case 17:
            printf("Semicolon or } expected.");
            break;
            
        case 18:
            printf("do expected.");
            break;
            
        case 19:
            printf("Incorrect symbol following statement.");
            break;
            
        case 20:
            printf("Relational operator expected.");
            break;
            
        case 21:
            printf("Expression must not contain a procedure identifier.");
            break;
            
        case 22:
            printf("Right parenthesis missing.");
            break;
            
        case 23:
            printf("The preceding factor cannot begin with this symbol.");
            break;
            
        case 24:
            printf("An expression cannot begin with this symbol.");
            break;
            
        case 25:
            printf("This number is too large.");
            break;
    }
}

void getNextToken() {
    token = LL->list[ptrLL++];
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
    getNextToken();
    block();
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
    char *temp = NULL;
    int numVars = 0;
    g_addr = 4;
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
                error(3);
                return 3;
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