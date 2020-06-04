#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "3_pipe.h"

#define FIFO "/tmp/myfifo"

int main(void){

	int fd;
	ssize_t count=0;
	char* myfifo=FIFO;
	int received=0;

	printf("\n\nProgram 3_pipe\n");
	
	fd = open(myfifo, O_RDONLY);
		
	count=read(fd, &received, sizeof(int));
	printf("Program 3_pipe otrzymal wartosc %i\n", received);
	count++;//TODO ususunac, kontrola bledu zrobic
	//long int numbersend = 848285;
	close(fd);
	send(received);	
	
return 0;
}


void send(const unsigned int number)
{
	int fd;    
	//char *pTxt=NULL;

	//asprintf(&pTxt, "%u", number);
	fd=open(CHRDEV_PATH,O_WRONLY);
	if(fd<0)
	{
		perror("Failed to open the device CHRDEV");
		exit(-1);
	}
	if( write(fd,(char*)&number,sizeof(int)) < 0 )//bylo sizeof(int)*8
	{
		perror("Couldn't write to CHRDEV");
		exit(-1);
	}
	close(fd);
	//free(pTxt);  raczej niepotrzebne
}
