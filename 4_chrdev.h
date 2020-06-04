#ifndef _4_CHRDEV_
#define _4_CHRDEV_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define CHRDEV_PATH "/dev/jajko"

long int receive();
//void gt_send(const unsigned int);
//long int transform(const long int);

#endif