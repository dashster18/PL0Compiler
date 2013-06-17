Instructions for using the PL/0 Compiler:

Step 1) Uploading files to Eustis:
     In order to be able to run the PL/0 compiler, you have to first load up your files onto the Eustis server. In order to do that, use the 'scp' command on the unix command line, Terminal. It is recommended you move all the source files and header files into one directory. The files are main.c, Parser.h, Scanner.h, and VM.h. If you want to save some time also, put your input file onto this directory also. Then execute the command  $ scp -r <directoryNameWithAllTheFiles> <nid>@eustis.eecs.ucf.edu:~/<insert path here>. This will move the directory you just created to Eustis. If you didn't include the input file in the directory, you can execute $ scp <inputFile> <nid>@eustis.eecs.ucf.edu:~/<insert path here>.
Step 2) Run Eustis
     Now run Eustis and find the location where you copied the file to.

Step 3) Compiling the PL/0 Compiler:
     Before you can use the compiler, you need to compile the source code first. In order to do that, use the 'gcc' command on the unix command line, Terminal. In this case, you only need to compile main.c, so we recommend you use
	 		$ gcc main.c -o PL0
	 This will create an executable file "PL0" which you can execute.

Step 4) Using the PL/0 Compiler:
	 In order to use the compiler, you need to execute the executable just created (In our example, it's called PL0 and for the purpose of this readme we are going to use that. You are free to call it whatever you like). The executable can also take in four optional argument: three flags for output and the input file name. 

The three flags you can pass are:
	-l: verbose output of the Lexical Analyzer. Prints the list of lexemes/tokens to the screen.
	-a: verbose output of the Parser. Prints the generated assembly code to the screen.
	-v: verbose output of the Virtual Machine. Prints the virtual machine execution trace to the screen.

If you don't provide an input file in the argument, the program will default to trying to read "test.pc". The following commands will run the program:
	 	
		$ ./PL0 (Runs the program "test.pc" which must be in the same directory as the executable)
		$ ./PL0 -l (Runs the program "test.pc" and prints the list of lexemes)
		$ ./PL0 -a (Runs the program "test.pc" and prints the generated assembly code)
		$ ./PL0 -v (Runs the program "test.pc" and prints the execution of the virtual machine)
		$ ./PL0 -l -a (Outputs the list of lexemes and the generated assembly code)
		$ ./PL0 -l -v (Outputs the list of lexemes and the execution of the virtual machine)
		$ ./PL0 -a -v (Outputs the generated assembly code and the execution of the virtual machine)
		$ ./PL0 -l -a -v (Outputs the list of lexemes, the generated assembly code, and the execution of the virtual machine)

		$ ./PL0 <inputFile> (Runs the program <inputFile> which must be in the same directory as the executable)
		$ ./PL0 -l <inputFile> (Runs the program <inputFile> and prints the list of lexemes)
		$ ./PL0 -a <inputFile> (Runs the program <inputFile> and prints the generated assembly code)
		$ ./PL0 -v <inputFile> (Runs the program <inputFile> and prints the execution of the virtual machine)
		$ ./PL0 -l -a <inputFile> (Outputs the list of lexemes and the generated assembly code)
		$ ./PL0 -l -v <inputFile> (Outputs the list of lexemes and the execution of the virtual machine)
		$ ./PL0 -a -v <inputFile> (Outputs the generated assembly code and the execution of the virtual machine)
		$ ./PL0 -l -a -v <inputFile> (Outputs the list of lexemes, the generated assembly code, and the execution of the virtual machine)

	Note when using an inputFile other than the default, it must be the last argument. If you also wish to use flags you must put them before the input filename.

	By default, the program outputs it's result to standard output. If you wish to output to file, you should redirect the output to a file:
	
		$ ./PL0 > <outputFile> OR
		$ ./PL0 <inputFile> > <outputFile>
		
		This will also work if you add any of the flags above.

and that's it!