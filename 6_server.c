#include "6_server.h"


void receive (int sock_fd) 
{ 
	char buff[MAX]; 
	int n; 
	// Odczytaj wiadomosc od klienta 
	read(sock_fd, buff, sizeof(buff)); 
	// Wyswietl wiadomosc od klienta 
	printf("Otrzymano wiadomość: %s ", buff); 
		
} 

// Funkcja servera nasłuchująca komunikaty wysyłane przez klienta. 
void run(int sock_fd) 
{ 
	char buff[MAX]; 
	int n; 
	// Nieskończona pętla nasłuchująca komunikaty od klienta 
	while(1)
	{ 
		// Odczytaj wiadomosc od klienta 
		read(sock_fd, buff, sizeof(buff)); 
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
int initialize_server(int *sock_fd) 
{ 
	int conn_fd, len; 
	struct sockaddr_in servaddr, cli; 

	// Utwórz serwer 
	*sock_fd = socket(AF_INET, SOCK_STREAM, 0); 
	if (*sock_fd == -1)
	{ 
		printf("Niepowodzenie w utworzeniu serwera...\n"); 
		exit(-1); 
	} 
	else
		printf("Pomyślnie utworzono gniazdo Socket...\n"); 
	
	bzero(&servaddr, sizeof(servaddr)); 

	// Przypisanie IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Połącz nowo stworzony serwer do podanego IP 
	if ((bind(*sock_fd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
	{ 
		printf("Połączenie serwera nie udało się...\n"); 
		perror("Error printed by perror");
		exit(-1); 
	} 
	else
		printf("Serwer został połączony \"binded\"..\n"); 

	// Serwer oczekuje na połączenie od klienta - nasłuchiwanie
	if ((listen(*sock_fd, 5)) != 0)
	{ 
		printf("Niepowodzenie nasłuchiwania...\n"); 
		exit(-1); 
	} 
	else
		printf("Serwer oczekuje na połączenie...\n"); 
	len = sizeof(cli); 

	// Zaakceptopwanie pakietu danych od klienta 
	conn_fd = accept(*sock_fd, (SA*)&cli, &len); 
	if (conn_fd < 0) 
	{ 
		printf("Nie udalo sie zaakceptowac polaczenia z klientem\n"); 
		exit(-1); 
	} 
	else
		printf("Pomyślnie zaakceptowano połączenie z klientem.\n"); 	
	
	// Zwróc deskryptor pliku do głównego programu
	return conn_fd;
}
	
int main()
{
	int sock_fd,conn_fd;
	
	conn_fd = initialize_server(&sock_fd);
	receive(conn_fd);
	close(sock_fd);

	printf ("Serwer zakończył działanie\n");
} 
