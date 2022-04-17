all: uab_sh hello fibonacci

uab_sh: shell.c
	gcc -o uab_sh shell.c
hello: hello.c
	gcc -o hello hello.c
fibonacci: fibonacci.c
	gcc -o fibonacci fibonacci.c
clean:
	rm *.o uab_sh hello fibonacci
