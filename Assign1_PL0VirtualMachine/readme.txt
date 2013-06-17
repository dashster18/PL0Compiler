Instructions to use the PM/0 virtual machine:

Step 1) Uploading files to Eustis:
     In order to be able to run the PM/0 VM, you have to first load up your files onto the Eustis server. In order to do that, use the 'scp' command on the unix command line, Terminal. For example, $ scp PM0.c <nid>@eustis.eecs.ucf.edu:~/<insert path here>. Then do this again for your input file.

Step 2) Run Eustis
     Now run Eustis and find the location where you copied the file to.

Step 3) Compiling the PM/0 VM:
     Before you can use the virtual machine, you need to compile it first. In order to do that, use the 'gcc' command on the unix command line, Terminal. For example, $ gcc PM0.c -o PM0.

Step 4) Using the PM/0 VM:
     In order to use the virtual machine, you need to change the input file's name into "P1.in". After that, move the input file and the executable created by the 'gcc' command in the same directory. Then change your present working directory to the directory the executable and the input file is in. After that, excute the command $ ./PM0. The virtual machine should run now and output a file, "P1.out" in which the output is.
