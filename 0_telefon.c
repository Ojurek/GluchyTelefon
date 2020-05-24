//program zarządzający - uruchamiający poszczególne stopnie w zależności od wykonania


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char command[50];
	int go;
	strcpy(command,"./1_konsola.o");
	printf("command %s ...\n", command);
	go=system(command);
	//printf("otrzymano liczbe goo %d \n\n", goo);

	return 0;
}
