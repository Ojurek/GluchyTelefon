CC = gcc -pthread -g -Wpedantic -Wall -Werror -pedantic-errors

all: compile run

compile:
	$(CC) 0_telefon.c -o 0_telefon.o
	$(CC) 1_konsola.c -o 1_konsola.o
	$(CC) 2_argument.c -o 2_argument.o
	$(CC) 3_pipe.c -o 3_pipe.o

run:
	./0_telefon.o

clean:
	rm -rf *.o
