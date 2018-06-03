all: f


f:  lab3_bubblesort.o
	gcc -g -Wall -o f lab3_bubblesort.o


lab3_bubblesort.o: lab3_bubblesort.c
	gcc -g -m64 -Wall -ansi -c -nostdlib -fno-stack-protector lab3_bubblesort.c -o lab3_bubblesort.o


clean:
	rm -f *.o
