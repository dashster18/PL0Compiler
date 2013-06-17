/* Written By: Nikesh Srivatava & Chris Anderson
 * ---- Version Table ----
 * |==============================================================|
 * | Ver   | Dates      | Author   | Comments                     |
 * |=======|============|==========|==============================|
 * | v0.1  | 2012.09.05 | Chris    | Original Code                |
 * |-------|------------|----------|------------------------------|
 * | v0.2  | 2012.09.05 | Nikesh   | Started Adding Stuff         |
 * |==============================================================|
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVEL 3

// This is our hard-coded array that contains the op-codes, where the op-code i is the obtained through accessing OPCODES[i].
char *const OPCODES[] = {"", "lit", "opr", "lod", "sto", "cal", "inc", "jmp", "jpc", "sio", "sio"};

// This struct defines our four registers that will store the state of CPU.
//  PC: Program Counter, holds the address of the current instruction being executed.
//  BP: Base Pointer, points to the bottom of the current activation record.
//  SP: Stack Pointer, points to the top of the stack.
//  IR: Holds the current instruction after it is fetched.
typedef struct CPU_REGISTERS {
    int PC;
    int BP;
    int SP;
    int IR;
} regFile;

// This struct defines the instruction format
//  OP: Operation code
//  L:  Lexicographical level
//  M:  Modifier
typedef struct INSTRUCTION_DATA {
    int OP;
    int L;
    int M;
} instruction;

// Signifies whether debug statements are on or off.
int debugFlag = 0;

// Prototypes for all our functions.
void debug(char* text);
void runPM0(FILE* fn1, FILE* fo2);

int main(int argc, char **argv){
    
    // Temporary String
    char *foobar;
    
    FILE* fn1; //PCODE IN
    FILE* fo2; //VM OUT
    
    
    // No input file. Use default.
    if(argc < 2) {
        fn1 = fopen("P1.in","rb");
        fo2 = fopen("P1.out","wb");
    }
    // Just an input file. Use declared string
    else if(argc == 2) {
        argc--; argv++;
        foobar = *argv;
        fn1 = fopen(foobar, "rb");
        
        argc--; argv++;
        foobar = *argv;
        fo2 = fopen(foobar,"wb");
    }
    // TBD: Flag indicating something special in the run.
    else {
        debug("Error: Parameter Format. Please try again!\n");
        return 1;
    }
    
    // Check for Input File Error
    if(fn1 == NULL) {
        debug("Error: Input file did not open correctly!\n");
        return 1;
    }
    
    // Check for Output File Error
    if(fo2 == NULL) {
        debug("Error: Output file did not open correctly!\n");
        return 1;
    }
    
    //Run the PM0 VM on input file, fn1, and release output to output file, fo2.
    runPM0(fn1,fo2);
    
}

// Prints the string passed in to screen.
void debug(char* text) {
    if(debugFlag) printf("%s",text);
}


void runPM0(FILE* fn1, FILE* fo2) {
    // When running the VM, make a stack and an instruction array
    int stack[MAX_STACK_HEIGHT];
    instruction code[MAX_CODE_LENGTH];
    int instructionCount = 0;
    
    // Read in the instructions into the instruction array
    while (fscanf(fn1, "%d%d%d ", &code[instructionCount].OP, &code[instructionCount].L, &code[instructionCount].M) != EOF) {
        // Increment the instructionIterator
        instructionCount++;
    }
    
    // Now that we have the instructions, we can now start the execution of the program.
}

/**********************************************/
/*		Find base L levels down               */
/*                                            */
/**********************************************/

// This is wrong, need to fix
int base(l, base) // l stand for L in the instruction format
{
    int b1; //find base L levels down
    b1 = base;
    while (l > 0)
    {
        b1 = stack[b1];
        l--;
    }
    return b1;
}
