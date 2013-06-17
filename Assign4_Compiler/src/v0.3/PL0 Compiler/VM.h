/* Written By: Chris Anderson & Nikesh Srivastava
 * ---- Version Table ----
 * |==============================================================|
 * | Ver   | Dates      | Author   | Comments                     |
 * |=======|============|==========|==============================|
 * | v0.1  | 2012.09.05 | Chris    | Original Code                |
 * |-------|------------|----------|------------------------------|
 * | v0.2  | 2012.09.05 | Nikesh   | Started Adding Stuff         |
 * |-------|------------|----------|------------------------------|
 * | v0.3  | 2012.09.06 | Nikesh   | Read in input and echoed     |
 * |       |            |          | Assembly code, fetch cycle,  |
 * |       |            |          | Start execute cycle 		  |
 * |       |            |          | Chris: Reviewed (9/6 12pm)   |
 * |-------|------------|----------|------------------------------|
 * | v0.4  | 2012.09.10 | Nikesh   | Filled in all functions      |
 * |-------|------------|----------|------------------------------|
 * | v0.5  | 2012.09.10 | Chris    | Added printing of stack      |
 * |-------|------------|----------|------------------------------|
 * | v0.6  | 2012.09.10 | Chris    | Fixed the base function and  |
 * |       |            |          | removed output file code.    |
 * |-------|------------|----------|------------------------------|
 * | v0.7  | 2012.09.17 | Nikesh   | Added finishing touches.     |
 * |==============================================================|
 *
 *
 */

#ifndef Parser_VM_h
#define Parser_VM_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVEL 3

// This is our hard-coded array that contains the op-codes, where the op-code i is the obtained through accessing OPCODES[i].
char *const OPCODES[] = {"", "lit", "opr", "lod", "sto", "cal", "inc", "jmp", "jpc", "sio", "sio"};

// This struct defines the instruction format
//  OP: Operation code
//  L:  Lexicographical level
//  M:  Modifier
typedef struct INSTRUCTION_DATA {
    int OP;
    int L;
    int M;
} instructionData;

// This struct defines our four registers that will store the state of CPU.
//  PC: Program Counter, holds the address of the current instruction being executed.
//  BP: Base Pointer, points to the bottom of the current activation record.
//  SP: Stack Pointer, points to the top of the stack.
//  IR: Holds the current instruction after it is fetched.
typedef struct CPU_REGISTERS {
    int PC;
    int BP;
    int SP;
    instruction IR;
} regFile;

// Signifies whether debug statements are on or off.
int debugFlag = 0;

// Prototypes for all our functions.
void debug(char* text);
void runPM0(FILE* fn1, FILE* fo2);
//void runPM0(FILE* fn1);
void execute(FILE *fo2, instruction code[], int stack[], regFile *registers);
//void execute(instruction code[], int stack[], regFile *registers);
int base(int l, int base, int stack[]);
void printStack(int stack[], regFile registers, FILE* fo2);

// Prints the string passed in to screen.
void debug(char* text) {
    if(debugFlag) printf("%s",text);
}

#endif
