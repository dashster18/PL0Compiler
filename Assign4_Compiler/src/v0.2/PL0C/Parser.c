/*
 * Parser.c
 *
 *  Created on: Nov 11, 2012
 *      Author: Chris
 */

#include "Parser.h"

/* Written by Christopher Anderson and Nikesh Srivastava */

typedef enum {
nulsym = 1, identsym, numbersym, plussym, minussym,
multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
periodsym, becomessym, beginsym, endsym, ifsym, thensym,
whilesym, dosym, callsym, constsym, intsym, procsym, outsym,
insym , elsesym } token_type;

int runParser(LexemeList *LLin){
    LL = LLin;
    ptrLL = 0;
    g_level = 0;
    g_addr = 0;
    if(initSymbolTable() != 0) return 1;
    getNextToken();

    if(program() != 0) return 1;

    int i;
    //printf("CX = %d\n",cx);
	for(i = 0; i < cx; i++) {
		printf("%d %d %d\n",code[i].op,code[i].l,code[i].m);
	}

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
    return x;
}

//Return 1 for fail, 0 for success
int insertConst(char* ID, int val) {
	printf("Inserted %s\n",ID);

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
	//printf("Inserted %s\n",ID);

    int hashval = hashName(ID);
    int i = hashval;
    int x = getTableSize();
    do {
        if(symbolTable[hashval].kind == 0)
        {
            symbolTable[hashval].kind = 2;
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
            symbolTable[hashval].kind = 3;
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
	//printf("Fetching ID Index - %s\n",ID);

    //THIS NEEDS TO BE FIXED ONCE WE CAN HAVE NESTED PROCEDURES!!!
    int hashval = hashName(ID);
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
	//printf("Program - token %d\n",token);
    int errorCode = 0;
    //getNextToken();
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
	//printf("Block\n");

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
    	//printf("Int Symbol Found!");

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
	//printf("Statement - token %d\n",token);

    int errorCode = 0;
    int temp, start;

    switch (token) {
        case identsym:
            getNextToken(); // Get the identifier
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
	//printf("Condition - token %d\n",token);
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
	//printf("Expression - token %d\n",token);
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
	//printf("Term - token %d\n",token);
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
	//printf("Factor - token %d\n",token);
    int errorCode = 0;
	int temp;

    switch (token) {
        case identsym:
			getNextToken();
			temp = fetchIDIndex(&token);
            //printf("Fetched: Index -> %d. Symbol - > %s. M -> %d. L -> %d\n",temp, symbolTable[temp].name,symbolTable[temp].addr,symbolTable[temp].level);
            if(symbolTable[temp].kind == 2)
            {
				emit(lod, symbolTable[temp].level,symbolTable[temp].addr);
            }
            else if(symbolTable[temp].kind == 1)
            {
				emit(lit, 0, symbolTable[temp].val);
			}
			else if(symbolTable[temp].kind == 3)
			{
				//Procedure
				error(21);
				return 21;
			}
			else
			{	
				//Kind is completely screwed up
				error(1);
				return 1;
			}
			
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





