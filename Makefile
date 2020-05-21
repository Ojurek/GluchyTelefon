CC = gcc

all:
	$(CC) telefon.c -o telefon.o
	$(CC) 1_program.c -o 1_program.out

run:
	./telefon.o
