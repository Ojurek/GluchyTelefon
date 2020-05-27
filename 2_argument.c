//Wejscie: argument do programu parsowany za pomoca getopt
//Modyfikacja/wyjscie x=Nastepna liczba pierwsza

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define FIFO "/tmp/myfifo"


int main(int argc, char* argv[]){

	int received;
	int fd;
	char* myfifo=FIFO;
	int status;
	ssize_t send=0;

	received = getopt(argc,argv,"0123456789")-'0';
	printf("Program 2_argument\n");
 	printf("drugi program otrzymal %i\n", received);

	//TODO obliczy nastpna liczbe pierwsza
	
	mkfifo(myfifo,0666);

	status = system("./3_pipe.o &");//probuje uruchomic w bg
	if (status==0){
		printf ("Wywolano trzeci program\n");
	}	

	fd = open(myfifo, O_WRONLY);
	printf("fd of pipe = %i\n", fd);
	
	//TODO obsuga bedu jesli nie otrzymamy fd
	send= write(fd, &received, 1); //TODO 1 zamienic na zmienna o wlasciwej dlugosci
	printf("wyslano bajtow %zd\n", send);
	close(fd);
	
	unlink(myfifo);
}
