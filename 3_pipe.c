#include "3_pipe.h"

static int fd_pipe;
static int fd_dev;    

int main(void){

	ssize_t count=0;
	char* myfifo=FIFO;
	uint32_t received=0;

	printf("\nProgram 3_pipe uruchomiony\n");

	catch_signal(SIGINT);
	
	fd_pipe = open(myfifo, O_RDONLY);
	
	while(1){	
		count=read(fd_pipe, &received, sizeof(uint32_t));
		if (count>0){
			printf("Program 3: orzymano liczbe: %i\n", received);
			received=set_bit(received);
			printf("Program 3: Wartosc po ustawieniu bitu = %i\n", received);
			send(received);
		}	
		sleep(0.5);
	}	

	
return 0;
}

uint32_t set_bit(uint32_t bit){
	
	uint32_t setted_int=0;

	setted_int = setted_int | (1<<bit);// operator przesunicia bitow o 5 miejsc w lewo 1<<5

	return setted_int;

}

void send(uint32_t received)
{


	fd_dev=open(CHRDEV_PATH,O_WRONLY);
	if(fd_dev<0)
	{
		perror("Program 3: Failed to open the device CHRDEV");
		killpg(getpgid(getpid()),SIGINT);
	}
	if( write(fd_dev,&received,sizeof(uint32_t)) < 0 )
	{
		perror("Program 3: Couldn't write to CHRDEV");
		killpg(getpgid(getpid()),SIGINT);
	}
}

void sig_handler(int sig, siginfo_t* info, void *uncotext){

	printf("Program 3: signal handler\n");
	close(fd_pipe);
	close(fd_dev);
	exit(0);
}

void catch_signal(int sig){
	static struct sigaction my_sigact;
	
	memset(&my_sigact,0,sizeof(my_sigact));
	my_sigact.sa_sigaction=sig_handler;
	my_sigact.sa_flags=SA_SIGINFO;

	sigaction(sig,&my_sigact,NULL);
}


