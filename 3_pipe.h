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

//funkcja wyślij po character device
void send(uint32_t received);

//funkcja ustawiająca bit na wymaganej pozycji position
uint32_t set_bit(uint32_t bit);

