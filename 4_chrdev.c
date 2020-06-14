//4.	"Jajko"
//◦	Wejście: interfejs znakowy (linux kernel module over chrdev)
//◦	Modyfikacja/wyjście: lustrzane odbicie bitów, np. dla x:= 524288 dec (bin: 00000000000010000000000000000000) dla x = 4096 dec (bin: 00000000000000000001000000000000)
//5.	"Netlink"
//◦	Wejście: Generic netlink  ---- netlink nie działa
//◦	Modyfikacja/wyjście:
//▪	x:= suma cyfr liczby x w postaci dziesiętnej


#include "4_chrdev.h"

static int fd_dev;
static int fd_sock;


int main(){

	uint32_t received;	
	ssize_t readed;	
	struct sockaddr_in servaddr;

	printf("\nProgram 4_chrdev uruchomiony\n");
	
	catch_signal(SIGINT);	

	///create socket
	fd_sock = socket(AF_INET, SOCK_STREAM, 0); 
	if (fd_sock == -1) { 
		printf("Program 4: Utworzenie socket nie powiodło się...\n"); 
		killpg(getpgid(getpid()),SIGINT);
	} 
	else {
		printf("Program 4: Socket utworzony..\n");
	}
 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	sleep(2);
	while (connect(fd_sock, (SA*)&servaddr, sizeof(servaddr)) != 0) 
	{ 
		printf("Program 4: Nieudana proba polaczenia z serwerem. Probuje dalej...\n"); 
		sleep(2);
	} 
	
	printf("Program 4: Połączony z serwerem.\n"); 

	fd_dev = open(CHRDEV_PATH, O_RDONLY);
		
	if (fd_dev < 0){
		perror("Program 4: Failed to open the device: CHRDEV");
		killpg(getpgid(getpid()),SIGINT);
 	}

	while (1){ 
		readed=read(fd_dev, &received, sizeof(uint32_t)); 
		if (readed < 0){
			perror("Program 4: Couldn't read from: CHRDEV");
			killpg(getpgid(getpid()),SIGINT);
		}
		
		if (readed>0){		
			printf("Program 4: orzymano liczbe: %i\n", received);
			received = lustrzane_odbicie(received);
			printf("Program 4: liczba po lustrzane odbicie = %i\n", received);
			received = sumowanie_cyfr(received);
			printf("Program 4: liczba po zsumowaniu cyfr = %i\n", received);
			write(fd_sock, &received, sizeof(uint32_t));
		}
		sleep(0.5);
	}

    return 0;
}

void sig_handler(int sig, siginfo_t* info, void *uncotext){

	printf("Program 4: signal handler\n");
	close(fd_dev);
	close(fd_sock); 
	exit(0);
}

void catch_signal(int sig){
	static struct sigaction my_sigact;
	
	memset(&my_sigact,0,sizeof(my_sigact));
	my_sigact.sa_sigaction=sig_handler;
	my_sigact.sa_flags=SA_SIGINFO;

	sigaction(sig,&my_sigact,NULL);
}

uint32_t lustrzane_odbicie(uint32_t number){

 	uint32_t transformed = 0;

	for (int i=0;i<32;i++){
		if ( (number & (1<<i)) > 0 ){
			transformed = transformed | (1<<(31-i));
		}
	}	

return transformed;
}

uint32_t sumowanie_cyfr(uint32_t number){

 	uint32_t transformed = 0;

	while (number>10){
		transformed += number % 10;
		number = number / 10;
	}	
	transformed +=number;

return transformed;
}


