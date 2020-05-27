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


	return 0;
}
