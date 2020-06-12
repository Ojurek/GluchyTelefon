//Character device implemented as kernel module driver receive program

#include "4_chrdev.h"

static int fd;
static int sockfd;

void sig_handler(int sig, siginfo_t* info, void *uncotext){

	printf("Program 4: signal handler\n");
	system("ps");
	close(fd);
	close(sockfd); 
	exit(0);
}

void catch_signal(int sig){
	static struct sigaction my_sigact;
	
	memset(&my_sigact,0,sizeof(my_sigact));
	my_sigact.sa_sigaction=sig_handler;
	my_sigact.sa_flags=SA_SIGINFO;

	sigaction(sig,&my_sigact,NULL);
}

int create_socket(){

	int sockfd; 
	struct sockaddr_in servaddr; 

	catch_signal(SIGINT);
	
	// Stwórz i zweryfikuj socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("Program 4: Utworzenie socket nie powiodło się...\n"); 
		exit(-1); 
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
	while (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) 
	{ 
		printf("Program 4: Nieudana proba polaczenia z serwerem. Probuje dalej...\n"); 
		sleep(2);
	} 
	
	printf("Program 4: Połączony z serwerem.\n"); 

	return sockfd;
} 



int main(){

	uint32_t received;	
	ssize_t readed=0;	
	ssize_t writed;

	printf("\nProgram 4_chrdev\n");

	sockfd=create_socket();

	fd = open(CHRDEV_PATH, O_RDONLY);
		
	if (fd < 0){
		perror("Program 4: Failed to open the device CHRDEV");
		exit(-1);
 	}

	while (1){ 
		readed=read(fd, &received, sizeof(uint32_t)); 
		if (readed < 0){
			perror("Program 4: Couldn't read from CHRDEV");
			exit(-1);
		}
		
		if (readed>0){		
			printf("Program 4 otrzymal wartosc %i\n", received);
			writed = write(sockfd, &received, sizeof(uint32_t));
			printf("Program 4 send %li bytes\n", writed);
		}
		sleep(0.5);
	}

    return 0;
}
