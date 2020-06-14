#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>

#define CHRDEV_PATH "/dev/jajko"
#define FIFO "/tmp/myfifo"

void sig_handler(int sig, siginfo_t* info, void *uncotext);
void catch_signal(int sig);	
void send(uint32_t received);
uint32_t set_bit(uint32_t bit);

