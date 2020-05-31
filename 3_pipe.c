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
	unsigned long int received=0;

	printf("Program 3_pipe\n");
	
	fd = open(myfifo, O_RDONLY);
	printf("program 3 otrzymal fd= %i",fd);
	count=read(fd, &received, 10); //TODO sprawdzic max dugosc
	printf("Program 3_pipe otrzymal wartosc %lu\n", received);
	printf("otrzymano bajtow %zd\n", count);
	
	long int numbersend = 848285;
	send(numbersend);


 	//close(fd);

return 0;
}


void send(const unsigned int number)
{
    int fd1;
    
    char *pTxt=NULL;
    asprintf(&pTxt, "%u", number);
    fd1=open(CHRDEV_PATH,O_WRONLY);
    if(fd1<0)
    {
        perror("Failed to open the device CHRDEV");
        exit(0);
    }
    if( write(fd1,pTxt,sizeof(int)*8) < 0 )
    {
        perror("Couldn't write to CHRDEV");
        exit(0);
    }
    close(fd1);
    free(pTxt);

}