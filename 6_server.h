#include <unistd.h>
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <errno.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

void sig_handler(int sig, siginfo_t* info, void *uncotext);
void catch_signal(int sig);	

