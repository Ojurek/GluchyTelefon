//Character device implemented as kernel module driver receive program

#include "4_chrdev.h"

int main()
{
    
    char buffer[225];
    sleep(1);
    printf("\n\nProgram 4_chrdev\n");
    long int number = receive();

    sprintf(buffer, "%ld", number);
    printf("odczytano z chr dev liczbe %s\n", buffer);
    return 0;
}


long int receive()
{
    int fd;
    char buffer[sizeof(int) * 8];
    fd = open(CHRDEV_PATH, O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open the device CHRDEV");
        exit(0);
    }

    if (read(fd, buffer, sizeof(int) * 8) < 0)
    {
        perror("Couldn't read from CHRDEV");
        exit(0);
    }
    close(fd);
    return atol(buffer);
}
