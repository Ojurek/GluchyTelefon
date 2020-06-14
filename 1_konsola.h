#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO "/tmp/myfifo"

void sig_handler(int sig, siginfo_t* info, void *uncotext);
void catch_signal(int sig);	
