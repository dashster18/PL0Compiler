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
 * |       |            |          |                              |
 * |==============================================================|
 *
 *   TBDs:
		1) Fill in execute functions.
 */

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
} instruction;

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
void execute(FILE *fout, instruction code[], int stack[], regFile *registers);

int main(int argc, char **argv){
    
    // Temporary String
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
    regFile registers;
    int instructionCount = 0, i;
    
    // Initialize registers
    registers.SP = 0;
    registers.BP = 1;
    registers.PC = 0;
    registers.IR.OP = 0;
    registers.IR.L = 0;
    registers.IR.M = 0;
    
    // Initialize stack
    for(i = 0; i < MAX_STACK_HEIGHT; i++) {
        stack[i] = 0;
    }
    
    // Read in the instructions into the instruction array
    while (fscanf(fn1, "%d%d%d ", &code[instructionCount].OP, &code[instructionCount].L, &code[instructionCount].M) != EOF) {
        // Increment the instructionIterator
        instructionCount++;
    }
    
    // Now that we have the instructions, we can now start the execution of the program.
    printf("Line\tOP\tL\tM\n");
    
    // Print out the instructions in assembly language format
    for(i = 0; i < instructionCount; i++) {
        printf("%4d\t%s\t%d\t%d\n", i, OPCODES[code[i].OP], code[i].L, code[i].M);
    }
    
    // Now we need to do the fetch and execute cycles for all the instructions
    for(i = 0; i < instructionCount; i++) {
        // Fetch: (Since it is one line of code, I decided not to write a function for it)
        //  IR <- code[PC]
        //  PC <- PC + 1
        registers.IR = code[registers.PC++];
        
        // Execute:
        execute(fo2, code, stack, &registers);
    }
}

// This is the execute cycle in the P-machine cycles.
//  fout: the file pointer to where output is printed
//  code: The code of the program currently being executed
//  stack: The stack for the current runtime environment
//  registers: Data structure containing all the registers of the CPU, reason for being a pointer is
//             because we want changes to be carried back to our runPM0 function.
void execute(FILE *fout, instruction code[], int stack[], regFile *registers) {
    // Use the op-code to figure out what instruction you will execute
    // instruction is stored in registers->IR
    
    // LIT 0, M
    //  Push a literal M onto the top of the stack
    if (registers->IR.OP == 1) {
        
    }
    // OPR 0, M
    //  Operation to be performed on the data at the top of the stack
    else if (registers->IR.OP == 2) {
        
    }
    // LOD L, M
    //  Load value to top of stack from the stack location at offset M from L lexicographical levels down
    else if (registers->IR.OP == 3) {
        
    }
    // STO L, M
    //  Store value at top of stack in the stack location at offset M from L lexicographical levels down
    else if (registers->IR.OP == 4) {
        
    }
    // CAL L, M
    //  Call procedure at code index M (generates new Activation Record and pc <- M)
    else if (registers->IR.OP == 5) {
        
    }
    // INC 0, M
    //  Allocate M locals (increment SP by M). First three are Static Link (SL), Dynamic Link (DL), and Return Address (RA)
    else if (registers->IR.OP == 6) {
        
    }
    // JMP 0, M
    //  Jump to instruction M
    else if (registers->IR.OP == 7) {
        
    }
    // JPC 0, M
    //  Jump to instruction M if top stack element is 0
    else if (registers->IR.OP == 8) {
        
    }
    // SIO 0, 1
    //  Write the top of the stack element to the screen
    else if (registers->IR.OP == 9) {
        
    }
    // SIO 0, 2
    //  Read an input from the user and store it at the top of the stack
    else if (registers->IR.OP == 10) {
        
    }
    // Instruction Input error, this instruction is not in the ISA
    else {
        
    }
}

/**********************************************/
/*		Find base L levels down               */
/*                                            */
/**********************************************/

/*
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
 */
