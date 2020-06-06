#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif


#include "3_pipe.h"

#define FIFO "/tmp/myfifo"

int main(void){

	int fd;
	ssize_t count=0;
	char* myfifo=FIFO;
	int received=0;
	char tekst [33];

	printf("\n\nProgram 3_pipe\n");
	
	fd = open(myfifo, O_RDONLY);
		
	count=read(fd, &received, sizeof(int));
	printf("Program 3_pipe otrzymal wartosc %i\n", received);
	set_byte(received, tekst);
	printf("String po ustawieniu bitu %s\n", tekst);
	count++;//TODO ususunac, kontrola bledu zrobic
	close(fd);
	send(tekst);	
	
return 0;
}

void set_byte(int position, char *tekst)
{
	int n = 31;
	while(n>=0)
	{
		tekst[n]='0';
		n--;
	}
	tekst[32]='\0';
	tekst[position-1]='1';
}


void send(char *tekst)
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
	if( write(fd,(char*)&tekst,sizeof(tekst)) < 0 )//bylo sizeof(int)*8
	{
		perror("Couldn't write to CHRDEV");
		exit(-1);
	}
	close(fd);
	//free(pTxt);  raczej niepotrzebne
}






