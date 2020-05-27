// to jest pierwszy plik
// pobiera argument z konsoli i przekazuje go do kolejnego programu
// uruchamiając go z parametrami obsługiwanymi przez get opt w 2 programie 

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
	unsigned long int liczba;
	int modulo; //wynik mozliwy od 0 do 9 
	char command[100]="./2_argument.o -";
	char result;
	int status;

	printf("Podaj liczbe dodatnia \n");
	scanf("%lu", &liczba);
	modulo = liczba % 10;
	result=modulo+'0';
	strcat(command, &result);

	printf("komenda to: %s\n", command);
	status = system(command);
	if (status==0){
		printf ("Wywolano drugi program\n");
	}
return 0;

}
