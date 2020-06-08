#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>

#define CHRDEV_PATH "/dev/jajko"

//funkcja wyślij po character device
void send(int received);

//funkcja ustawiająca bit na wymaganej pozycji position
int set_bit(int bit);

