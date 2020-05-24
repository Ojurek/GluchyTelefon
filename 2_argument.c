//Wejscie: argument do programu parsowany za pomoca getopt
//Modyfikacja/wyjscie x=Nastepna liczba pierwsza

#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[]){

	int received;


	received = getopt(argc,argv,"0123456789");
	printf("\nProgram 2_argument\n");
	printf("argc: %i\n", argc);
	printf("argv[0]: %s\n", argv[0]);
	printf("argv[1]: %d\n", argv[1][0]-'0');
 

	printf("drugi program otrzymal %i\n", received);
}
