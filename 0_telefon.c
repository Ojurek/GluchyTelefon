//program zarządzający - uruchamiający poszczególne stopnie w zależności od wykonania


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
		system("./4_chrdev.o &");
	system("./1_konsola.o");
	printf("zakonczenie działania programow 1-3\n");

	printf("zakonczenie działania telefon.o\n");

	return 0;
}
