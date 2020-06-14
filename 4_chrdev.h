#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <netdb.h> 
#include <string.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

#define CHRDEV_PATH "/dev/jajko"

void sig_handler(int sig, siginfo_t* info, void *uncotext);
void catch_signal(int sig);	
uint32_t lustrzane_odbicie(uint32_t number);
uint32_t sumowanie_cyfr(uint32_t number);





