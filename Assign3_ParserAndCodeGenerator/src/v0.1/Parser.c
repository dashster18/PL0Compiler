/* Written by Christopher Anderson and Nikesh Srivastava */

#include "Scanner.c"

int main(int argc, const char * argv[])
{
    
    return 0;
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

/*
 procedure PROGRAM;
 begin
 GET(TOKEN);
 BLOCK;
 if TOKEN != "periodsym" then ERROR
 end;
 */

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