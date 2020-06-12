#include "6_server.h"

static int sock_fd;

void sig_handler(int sig, siginfo_t* info, void *uncotext){

	printf("Program 6: signal handler\n");
	system("ps");
	close(sock_fd);
	exit(0);
}

void catch_signal(int sig){
	static struct sigaction my_sigact;
	
	memset(&my_sigact,0,sizeof(my_sigact));
	my_sigact.sa_sigaction=sig_handler;
	my_sigact.sa_flags=SA_SIGINFO;

	sigaction(sig,&my_sigact,NULL);
}

int initialize_server(int *sock_fd) 
{ 
	int conn_fd;
	socklen_t len; 
	struct sockaddr_in servaddr, cli; 

	// Utwórz serwer 
	*sock_fd = socket(AF_INET, SOCK_STREAM, 0); 
	if (*sock_fd == -1)
	{ 
		printf("Program 6: Niepowodzenie w utworzeniu serwera...\n"); 
		exit(-1); 
	} 
	else
		printf("Program 6: Pomyślnie utworzono gniazdo Socket...\n"); 
	
	bzero(&servaddr, sizeof(servaddr)); 

	// Przypisanie IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Połącz nowo stworzony serwer do podanego IP 
	if ((bind(*sock_fd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("Program 6: Połączenie serwera nie udało się...\n"); 
		perror("Program 6: Error printed by perror");
		exit(-1); 
	} 
	else
		printf("Program 6: Serwer został połączony \"binded\"..\n"); 

	// Serwer oczekuje na połączenie od klienta - nasłuchiwanie
	if ((listen(*sock_fd, 5)) != 0) { 
		printf("Program 6: Niepowodzenie nasłuchiwania...\n"); 
		exit(-1); 
	} 
	else {
		printf("Program 6: Serwer oczekuje na połączenie...\n"); 
	}

	len = sizeof(cli); 

	// Zaakceptopwanie pakietu danych od klienta 
	conn_fd = accept(*sock_fd, (SA*)&cli, &len); 
	if (conn_fd < 0) { 
		printf("Program 6: Nie udalo sie zaakceptowac polaczenia z klientem\n"); 
		exit(-1); 
	} 
	else {
		printf("Program 6: Pomyślnie zaakceptowano połączenie z klientem.\n"); 
	}	
	
	// Zwróc deskryptor pliku do głównego programu
	return conn_fd;
}

	
int main(){

	int conn_fd;
	uint32_t received;	 
	
	printf("\nProgram 6_server uruchomiony\n");

	catch_signal(SIGINT);

	conn_fd = initialize_server(&sock_fd);
	printf("\nProgram 6: zainicjowany\n");	
	while(1){	
		if (read(conn_fd, &received, sizeof(uint32_t))>0){ 
			printf("Program 6 otrzymal wiadomość: %i ", received); 
		}
	sleep(0.5);
	}
} 
