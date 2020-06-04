// to jest pierwszy plik
// pobiera argument z konsoli i przekazuje go do kolejnego programu
// uruchamiając go z parametrami obsługiwanymi przez get opt w 2 programie 

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>

static int pid_program_4;

void sig_handler(int sig, siginfo_t* info, void *uncotext){

	printf("sig_handler\n");
	system("ps");
	kill (pid_program_4, SIGTERM);//TODO poprawic
	sleep(2);
	//kill (pid_program_4, SIGKILL);
	system("ps");
	exit(0);
}



void catch_signal(int sig){
	static struct sigaction my_sigact;
	
	memset(&my_sigact,0,sizeof(my_sigact));
	my_sigact.sa_sigaction=sig_handler;
	my_sigact.sa_flags=SA_SIGINFO;

	sigaction(sig,&my_sigact,NULL);
}


int main ()
{
	uint32_t liczba;
	int modulo; //wynik mozliwy od 0 do 9 
	char command_pre[]="./2_argument.o -";	
	char command[]="./2_argument.o -";
		
	char result;
	int status;
	pid_t proc;
	
	printf("\n\nProgram 1_konsola\n");
	
	catch_signal(SIGINT);

	//start program 6
	//

	//start program 5

	//start program 4
	proc=fork();
	if (proc==0){
		pid_program_4=getpid();
		execl("./4_chrdev.o","4_chrdev.o", NULL);
	}	
	
	while (1){
		printf("Podaj liczbe dodatnia \n");
		scanf("%u", &liczba);
		modulo = liczba % 10;
		result=modulo+'0';
		strcat(command, &result);

		status = system(command);
		if (status!=0){
			printf ("program drugi zwrocil blad\n");
		}
		sleep(1);
		strcpy(command,command_pre);
	}
return 0;

}
