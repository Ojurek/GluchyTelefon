
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 


void func (int sockfd) 
{ 
	char buffer[MAX]; 
	size_t bufsize = MAX;
	int n; 
	while(1)
	{ 
		printf("Wprowadź wiadomość : "); 
		n = 0;
		fgets(buffer, MAX, stdin);
		write(sockfd, buffer, sizeof(buffer)); 
				
		if ((strncmp(buffer, "exit", 4)) == 0) 
		{ 
			printf("Zamknij klienta...\n"); 
			break; 
		} 
	} 
} 

void send_m (int sockfd) 
{ 
	char buffer[MAX]; 
	size_t bufsize = MAX;
	int n; 
	printf("Wprowadź wiadomość : "); 
	fgets(buffer, MAX, stdin);
	write(sockfd, buffer, sizeof(buffer)); 
} 

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	// Stwórz i zweryfikuj socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) 
	{ 
		printf("Utworzenie socket nie powiodło się...\n"); 
		exit(-1); 
	} 
	else
		printf("Socket utworzony..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) 
	{ 
		printf("Połączenie z serwerem nie udało się.\n"); 
		exit(-1); 
	} 
	else
		printf("Połączony z serwerem.\n"); 

	send_m(sockfd);

	close(sockfd); 
} 
