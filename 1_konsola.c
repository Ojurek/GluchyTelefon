//1.	"Konsola":
//◦	Wejście: stdin
//◦	Modyfikacja/wyjście: x:=x modulo 10


#include "1_konsola.h"

int main ()
{
	uint32_t liczba;
	int modulo; //wynik mozliwy od 0 do 9 
	char command_pre[]="./2_argument.o -";	
	char command[]="./2_argument.o -";
		
	char result;
	int status;
	pid_t proc;
	
	printf("Program 1_konsola uruchomiony\n");
	
	catch_signal(SIGINT);

	//start program 6
	proc=fork();
	if (proc==0){
		execl("./6_server.o","6_server.o", NULL);
	}	

	//create pipe for program 3 - 4
	mkfifo(FIFO,0666);

	//start program 4
	proc=fork();
	if (proc==0){
		execl("./4_chrdev.o","4_chrdev.o", NULL);
	}	

	//start program 3
	proc=fork();
	if (proc==0){
		execl("./3_pipe.o","3_pipe.o", NULL);
	}	
		
	while (1){		
		sleep(5);
		printf("\nProgram 1: Podaj calkowita liczbe dodatnia: ");
		scanf("%u", &liczba);
		modulo = liczba % 10;
		result=modulo+'0';
		strcat(command, &result);

		status = system(command);
		if (status!=0){
			printf ("Program 1: Program drugi zwrocil blad\n");
			killpg(getpgid(getpid()),SIGINT);
		}
		strcpy(command,command_pre);
	}
	return 0;
}

void sig_handler(int sig, siginfo_t* info, void *uncotext){

	printf("Program 1: signal handler\n");
	sleep(2);
	unlink(FIFO);
	printf("Program 1: exit\n");
	exit(0);
}

void catch_signal(int sig){
	static struct sigaction my_sigact;
	
	memset(&my_sigact,0,sizeof(my_sigact));
	my_sigact.sa_sigaction=sig_handler;
	my_sigact.sa_flags=SA_SIGINFO;

	sigaction(sig,&my_sigact,NULL);
}
