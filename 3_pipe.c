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

	printf("\n\nProgram 3_pipe\n");
	
	fd = open(myfifo, O_RDONLY);
		
	count=read(fd, &received, sizeof(int));
	printf("Program 3_pipe otrzymal wartosc %i\n", received);

	received=set_bit(received);

	printf("Wartosc po ustawieniu bitu %i\n", received);
	count++;//TODO ususunac, kontrola bledu zrobic
	close(fd);
	send(received);	
	
return 0;
}

int set_bit(int bit){
// operator przesunicia bitow o 5 miejsc w lewo 1<<5
	
	int setted_int=0;
	setted_int = setted_int | (1<<bit);
	// lub 	*v |= (1<<bit);

	return setted_int;

}
/*
int set_bit(int position, char *tekst)
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
*/

void send(int received)
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
	if( write(fd,&received,sizeof(int)) < 0 )
	{
		perror("Couldn't write to CHRDEV");
		exit(-1);
	}
	close(fd);
	//free(pTxt);  raczej niepotrzebne
}






