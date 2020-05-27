#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO "/tmp/FIFO"

int main(void){

	int fd;
	ssize_t count=0;
	char* myfifo=FIFO;
	unsigned long int received=0;

	printf("Program 3_pipe\n");
	
	fd = open(myfifo, O_RDONLY);
	sleep(5);

	count=read(fd, &received, 10); //TODO sprawdzic max dugosc
	printf("Program 3_pipe otrzymal wartosc %lu\n", received);
	printf("otrzymano bajtow %zd\n", count);


 	//close(fd);

return 0;
}
