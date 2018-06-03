all: f

f:  main.o
	gcc  -g -Wall -o f main.o

main.o: main.c
	gcc -g -m64 -Wall -c -o main.o main.c

clean:
	rm -f *.o
