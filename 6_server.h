#ifndef _6_SERVER_
#define _6_SERVER_

#include <unistd.h>
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <errno.h>

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

void run(int sockfd);
int initialize_server(int *sockfd);
void receive (int sockfd) ;
	
#endif