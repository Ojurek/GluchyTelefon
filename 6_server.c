#include "6_server.h"

static int fd_sock;

int main(){

	int conn_fd;
	uint32_t received;	
	socklen_t len; 
	struct sockaddr_in servaddr, cli;  
	
	printf("Program 6_server uruchomiony\n");

	catch_signal(SIGINT);

	//////inicjacja serwera

	// Utwórz serwer 
	fd_sock = socket(AF_INET, SOCK_STREAM, 0); 
	if (fd_sock == -1)
	{ 
		printf("Program 6: Niepowodzenie w utworzeniu serwera...\n"); 
		killpg(getpgid(getpid()),SIGINT);
	} 
	else
		printf("Program 6: Pomyślnie utworzono gniazdo Socket...\n"); 
	
	bzero(&servaddr, sizeof(servaddr)); 

	// Przypisanie IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Połącz nowo stworzony serwer do podanego IP 
	if ((bind(fd_sock, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("Program 6: Połączenie serwera nie udało się...\n"); 
		perror("Program 6: Error printed by perror");
		killpg(getpgid(getpid()),SIGINT);
	} 
	else
		printf("Program 6: Serwer został połączony \"binded\"..\n"); 

	// Serwer oczekuje na połączenie od klienta - nasłuchiwanie
	if ((listen(fd_sock, 5)) != 0) { 
		printf("Program 6: Niepowodzenie nasłuchiwania...\n"); 
		killpg(getpgid(getpid()),SIGINT);
	} 
	else {
		printf("Program 6: Serwer oczekuje na połączenie...\n"); 
	}

	len = sizeof(cli); 

	// Zaakceptopwanie pakietu danych od klienta 
	conn_fd = accept(fd_sock, (SA*)&cli, &len); 
	if (conn_fd < 0) { 
		printf("Program 6: Nie udalo sie zaakceptowac polaczenia z klientem\n"); 
		killpg(getpgid(getpid()),SIGINT);
	} 
	else {
		printf("Program 6: Pomyślnie zaakceptowano połączenie z klientem.\n"); 
	}	
	///koniec inicjalizacji serwera
	
	while(1){	
		read(conn_fd, &received, sizeof(uint32_t)); 
		printf("Program 6: orzymano liczbe: %i\n", received); 
		sleep(0.5);
	}
} 

void sig_handler(int sig, siginfo_t* info, void *uncotext){

	printf("Program 6: signal handler\n");
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
