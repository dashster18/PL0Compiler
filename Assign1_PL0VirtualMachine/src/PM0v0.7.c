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
//void runPM0(FILE* fn1);
void execute(FILE *fo2, instruction code[], int stack[], regFile *registers);
//void execute(instruction code[], int stack[], regFile *registers);
int base(int l, int base, int stack[]);
void printStack(int stack[], regFile registers, FILE* fo2);

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
    //    if(fo2 == NULL) {
    //        debug("Error: Output file did not open correctly!\n");
    //        return 1;
    //    }
    
    //Run the PM0 VM on input file, fn1, and release output to output file, fo2.
    runPM0(fn1,fo2);
    //runPM0(fn1);
    
}

// Prints the string passed in to screen.
void debug(char* text) {
    if(debugFlag) printf("%s",text);
}


void runPM0(FILE* fn1, FILE* fo2) {
    //void runPM0(FILE* fn1) {
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
    fprintf(fo2,"Line  OP   L   M\n");
    
    // Print out the instructions in assembly language format
    for(i = 0; i < instructionCount; i++) {
        fprintf(fo2," %3d %3s %3d %3d\n", i, OPCODES[code[i].OP], code[i].L, code[i].M);
    }
    
    fprintf(fo2,"\n");
    fprintf(fo2,"Line  OP   L   M  pc  bp  sp  stack\n");
    fprintf(fo2,"  Initial Values   0   1   0  -EMPTY-\n");
    
    // Now we need to do the fetch and execute cycles for all the instructions
    //for(i = 0; i < instructionCount; i++) {
    while(registers.BP > 0) { //CJA - TBD - Changed this because we don't go for "instruction count" times. We go until the base pointer is dead. ( THIS NEEDS TO BE CONFIRMED! )
        // Fetch: (Since it is one line of code, I decided not to write a function for it)
        //  IR <- code[PC]
        //  PC <- PC + 1
        registers.IR = code[registers.PC++];
        fprintf(fo2," %3d %3s %3d %3d", registers.PC-1, OPCODES[code[registers.PC-1].OP], code[registers.PC-1].L, code[registers.PC-1].M);
        // Execute:
        execute(fo2, code, stack, &registers);
        //execute(code, stack, &registers);
        fprintf(fo2," %3d %3d %3d ", registers.PC, registers.BP, registers.SP);
        //for(j = 0; j <= registers.SP; j++) {
        //            printf(" %d", stack[j]);
        //        }
        //        printf("\n");
        printStack(stack, registers, fo2);
        fprintf(fo2,"\n");
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
    if (registers->IR.OP == 1) {
        registers->SP = registers->SP + 1;
        stack[registers->SP] = registers->IR.M;
    }
    // OPR 0, M
    //  Operation to be performed on the data at the top of the stack
    else if (registers->IR.OP == 2) {
        // Execute the instruction that is signified by the M value
        
        // RET
        if (registers->IR.M == 0) {
            registers->SP = registers->BP - 1;
            registers->PC = stack[registers->SP + 4];
            registers->BP = stack[registers->SP + 3];
        }
        // NEG
        else if (registers->IR.M == 1) {
            // No idea what you're supposed to do with -stack[sp]
            // Not sure if this is correct
            stack[registers->SP] = -1 * stack[registers->SP];
        }
        // ADD
        else if (registers->IR.M == 2) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] + stack[registers->SP + 1];
        }
        // SUB
        else if (registers->IR.M == 3) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] - stack[registers->SP + 1];
        }
        // MUL
        else if (registers->IR.M == 4) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] * stack[registers->SP + 1];
        }
        // DIV
        else if (registers->IR.M == 5) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] / stack[registers->SP + 1];
        }
        // ODD
        else if (registers->IR.M == 6) {
            // Mistake in document, please verify
            stack[registers->SP] = stack[registers->SP] % 2;
        }
        // MOD
        else if (registers->IR.M == 7) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] % stack[registers->SP + 1];
        }
        // EQL
        else if (registers->IR.M == 8) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] == stack[registers->SP + 1];
        }
        // NEQ
        else if (registers->IR.M == 9) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] != stack[registers->SP + 1];
        }
        // LSS
        else if (registers->IR.M == 10) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] < stack[registers->SP + 1];
        }
        // LEQ
        else if (registers->IR.M == 11) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] <= stack[registers->SP + 1];
        }
        // GTR
        else if (registers->IR.M == 12) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] > stack[registers->SP + 1];
        }
        // GEQ
        else if (registers->IR.M == 13) {
            registers->SP = registers->SP - 1;
            stack[registers->SP] = stack[registers->SP] >= stack[registers->SP + 1];
        }
    }
    // LOD L, M
    //  Load value to top of stack from the stack location at offset M from L lexicographical levels down
    else if (registers->IR.OP == 3) {
        registers->SP = registers->SP + 1;
        stack[registers->SP] = stack[base(registers->IR.L, registers->BP, stack) + registers->IR.M];
    }
    // STO L, M
    //  Store value at top of stack in the stack location at offset M from L lexicographical levels down
    else if (registers->IR.OP == 4) {
        stack[base(registers->IR.L, registers->BP, stack) + registers->IR.M] = stack[registers->SP];
        registers->SP = registers->SP - 1;
    }
    // CAL L, M
    //  Call procedure at code index M (generates new Activation Record and pc <- M)
    else if (registers->IR.OP == 5) {
        stack[registers->SP + 1] = 0;               // Spot for functional return value
        stack[registers->SP + 2] = base(registers->IR.L, registers->BP, stack);        // Static Link
        stack[registers->SP + 3] = registers->BP;   // Dynamic Link
        stack[registers->SP + 4] = registers->PC;   // Return Address
        registers->BP = registers->SP + 1;
        registers->PC = registers->IR.M;
    }
    // INC 0, M
    //  Allocate M locals (increment SP by M). First three are Static Link (SL), Dynamic Link (DL), and Return Address (RA)
    else if (registers->IR.OP == 6) {
        registers->SP = registers->SP + registers->IR.M;
    }
    // JMP 0, M
    //  Jump to instruction M
    else if (registers->IR.OP == 7) {
        registers->PC = registers->IR.M;
    }
    // JPC 0, M
    //  Jump to instruction M if top stack element is 0
    else if (registers->IR.OP == 8) {
        if (stack[registers->SP] == 0) {
            registers->PC = registers->IR.M;
        }
        registers->SP = registers->SP - 1;
    }
    // SIO 0, 1
    //  Write the top of the stack element to the screen
    else if (registers->IR.OP == 9) {
        printf("%d", stack[registers->SP]);
        registers->SP = registers->SP - 1;
    }
    // SIO 0, 2
    //  Read an input from the user and store it at the top of the stack
    else if (registers->IR.OP == 10) {
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
    
    if (registers.IR.OP == 5) {
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
            buffer[j++] = -1;
            mBP = mDL;
            mDL = stack[mBP + 2];
            if(mBP > registers.BP) getchar();
        }
    }
    //buffer[j] = '\0';
    if(j == 0) fprintf(fo2," -EMPTY- ");
    if(max < 100){
        for(j = j; j > 0; j--) {
            if(buffer[j] == -1) {
                fprintf(fo2,"  |");
            }
            else {
                fprintf(fo2," %2d", buffer[j]);
            }
        }
    }
    else if(max < 1000) {
        for(j = j; j > 0; j--) {
            if(buffer[j] == -1) {
                fprintf(fo2,"   |");
            }
            else {
                fprintf(fo2," %3d", buffer[j]);
            }
        }
    }
    else {// if(max < 10000) {
        for(j = j; j > 0; j--) {
            if(buffer[j] == -1) {
                fprintf(fo2,"    |");
            }
            else {
                fprintf(fo2," %4d", buffer[j]);
            }
        }
    }
    
} //End of printStack



