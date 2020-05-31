#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define CHRDEV_PATH "/dev/jajko"

//funkcja wyślij po character device
void send(const unsigned int number);