//Wejscie: argument do programu parsowany za pomoca getopt
//Modyfikacja/wyjscie x=Nastepna liczba pierwsza

#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[]){

	int received;


	received = getopt(argc,argv,"0123456789")-'0';
	printf("\nProgram 2_argument\n");

 	printf("drugi program otrzymal %i\n", received);
}
