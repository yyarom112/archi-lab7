all: hexeditplus

hexeditplus:  task1.o
	gcc -g -Wall -o hexeditplus task1.o

task1.o: task1.c
	gcc -g -Wall -c -o task1.o task1.c

clean:
	rm -f *.o
