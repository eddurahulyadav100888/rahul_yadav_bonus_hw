# Shell in C

In computing, a shell is a computer program which exposes an operating system's services to a human user or other programs. In general, operating system shells use either a command-line interface or graphical user interface, depending on a computer's role and particular operation.
In this project we are creating a minimal shell with few basic functionalities using C programming language.

Shell is implemented in the file shell.c.
hello.c for printing out a "Hello World!" message whereas fibonacci.c prints out fibonacci series upto a number.

# Author
# Acknowledgment
# Getting Started
## Prerequisites/Dependencies
	There are no third party libraries required for this project.
	But following header files are required:
	```
	#include <stdio.h>
	#include <stdlib.h>	
	#include <unistd.h>
	#include <string.h>
	#include <sys/wait.h>
	#include <dirent.h>
	```
## Instructions for building/compiling
- Compilation is done using a Makefile. In a terminal type 'make' for compiling all three files.
- ./uab_sh will run the shell.

# Testing:
1. **./uab_sh**	: This will open our shell prompt ie "uab_sh>".
2. **list**	: List out contents of the current directory.
3. **help**	: Print out the available commands.
4. **cd ..**	: This will change the working directory, for confirmation type list again you can see the change in contents.
5. **./hello**	: Run the hello world program.
6. **./fibonacci 10**	: Print out 10 fibonacci terms.
7. **./fibonacci**	: Print out fibonacci terms upto a number specified by the user.
8. **quit**	: This will exit out into yout default terminal.

# Screenshots
- Compiling:

![Compiling using Makefile](screenshots/make.png)

- List command:

![List](screenshots/list.png)

- Hello and Fibonacci:

![List](screenshots/hello_fibonacci.png)

- History:

![List](screenshots/history.png)

- cd directory:

![List](screenshots/cd.png)

- Help and Quit:

![List](screenshots/help.png)

# Contact Information

