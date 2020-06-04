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
	ssize_t send=0;
	pid_t proc;
	
	received = getopt(argc,argv,"0123456789")-'0';
	printf("\n\nProgram 2_argument\n");
 	printf("Drugi program otrzymal %i\n", received);

	//TODO obliczy nastpna liczbe pierwsza
	
	mkfifo(myfifo,0666);

//	system("./3_pipe.o");

	proc=fork();

	if (proc==0){
		execl("./3_pipe.o","3_pipe.o", NULL);
	}	

	fd = open(myfifo, O_WRONLY);
	
	//TODO obsuga bledu jesli nie otrzymamy fd
	send= write(fd, &received, sizeof(int)); 
	send++;//TODO usunac
	close(fd);	
	unlink(myfifo);
return 0;
}
