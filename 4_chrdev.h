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

long int receive();
//void gt_send(const unsigned int);
//long int transform(const long int);






