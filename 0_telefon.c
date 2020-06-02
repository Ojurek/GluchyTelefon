//program zarządzający - uruchamiający poszczególne stopnie w zależności od wykonania


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char command[50];
	strcpy(command,"./1_konsola.o");
	printf("command %s ...\n", command);
	system(command);
	printf("zakonczenie działania programow 1-3\n");
	char command2[20]="./4_chrdev.o";
	system(command2);
	printf("zakonczenie działania telefon.o\n");

	return 0;
}
