#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LEN 500
#define MAX_LEXI_LEVEL 3

struct {
	

int debug_flag = 0;

void debug(char* text, int debug_flag);
void runPM0(FILE* fn1, FILE* fo2);

int main(int argc, char **argv){
	char *foobar;
	
	FILE* fn1; //PCODE IN
	FILE* fo2; //VM OUT
	
	
	// No input file. Use default.
	if(argc < 2) {
		fn1 = fopen("P1.in","rb");
		fo2 = fopen("P1.out","wb");
	}// Just an input file. Use declared string
	else if(argc == 2) {
		argc--; argv++;
		foobar = *argv;
		fn1 = fopen(foobar, "rb");
		
		argc--; argv++;
		foobar = *argv;
		fo2 = fopen(foobar,"wb");
	} // TBD: Flag indicating something special in the run.
	else {
		debug("Error: Parameter Format. Please try again!\n");
		return 1;
	}
	
	// Check for Input File Error
	if(fn1 == null) {
		debug("Error: Input file did not open correctly!\n");
		return 1;
	}
	
	// Check for Output File Error
	if(fo2 == null) {
		debug("Error: Output file did not open correctly!\n");
		return 1;
	}
	
	//Run the PM0 VM on input file, fn1, and release output to output file, fo2.
	runPM0(fn1,f02);
	
}

// Debug statements
void debug(char* text) {
	if(debug_flag) printf("%s",text);
}

void runPM0(FILE* fn1, FILE* fo2) {
	
	
	
	
}