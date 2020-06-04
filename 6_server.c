#include "6_server.h"


void receive (int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	// Odczytaj wiadomosc od klienta 
	read(sockfd, buff, sizeof(buff)); 
	// Wyswietl wiadomosc od klienta 
	printf("Otrzymano wiadomość: %s ", buff); 
		
} 

// Funkcja servera nasłuchująca komunikaty wysyłane przez klienta. 
void run(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	// Nieskończona pętla nasłuchująca komunikaty od klienta 
	while(1)
	{ 
		// Odczytaj wiadomosc od klienta 
		read(sockfd, buff, sizeof(buff)); 
		// Wyswietl wiadomosc od klienta 
		printf("Otrzymano wiadomość: %s ", buff); 
		
		// Jesli wiadomosc zawiera 'exit' zakończ działanie pętli 
		if (strncmp("exit", buff, 4) == 0) 
		{ 
			printf("Serwer zamyka się...\n"); 
			break; 
		} 
	} 
} 

// Inicjalizacja serwera
int initialize_server(int *sockfd) 
{ 
	int connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// Utwórz serwer 
	*sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (*sockfd == -1)
	{ 
		printf("Niepowodzenie w utworzeniu serwera...\n"); 
		exit(0); 
	} 
	else
		printf("Pomyślnie utworzono gniazdo Socket...\n"); 
	
	bzero(&servaddr, sizeof(servaddr)); 

	// Przypisanie IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Połącz nowo stworzony serwer do podanego IP 
	if ((bind(*sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
	{ 
		printf("Połączenie nie udało się...\n"); 
		perror("Error printed by perror");
		exit(0); 
	} 
	else
		printf("Serwer został połączony \"binded\"..\n"); 

	// Serwer oczekuje na połączenie od klienta - nasłuchiwanie
	if ((listen(*sockfd, 5)) != 0)
	{ 
		printf("Niepowodzenie nasłuchiwania...\n"); 
		exit(0); 
	} 
	else
		printf("Serwer oczekuje na połączenie...\n"); 
	len = sizeof(cli); 

	// Zaakceptopwanie pakietu danych od klienta 
	connfd = accept(*sockfd, (SA*)&cli, &len); 
	if (connfd < 0) 
	{ 
		printf("Niepowodzenie acept...\n"); 
		exit(0); 
	} 
	else
		printf("Pomyślnie zaakceptowano połączenie z klientem...\n"); 	
	
	// Zwróc deskryptor pliku do głównego programu
	return connfd;
}
	
int main()
{
	int sockfd,connfd;
	
	connfd = initialize_server(&sockfd);
	receive(connfd);
	close(sockfd);

	/*
	connfd = initialize_server(&sockfd);
	receive(connfd);
	close(sockfd);*/
	
	
	printf ("Serwer zakończył działanie\n");
} 
