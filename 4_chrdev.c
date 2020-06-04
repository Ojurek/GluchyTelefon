//Character device implemented as kernel module driver receive program

#include "4_chrdev.h"

int main(){

	int received;	
	int fd;
	ssize_t readed=0;
	
	fd = open(CHRDEV_PATH, O_RDONLY);
		
	if (fd < 0){
		perror("Failed to open the device CHRDEV");
		exit(-1);
 	}

	while (readed<=0){ 
		readed=read(fd, (char*)&received, sizeof(int)); 
		if (readed < 0){
			perror("Couldn't read from CHRDEV");
			exit(-1);
		}
		
		if (readed>0){		
			printf("Program 4_chrdev otrzymal wartosc %i\n", received);
			readed=0;
		}
		sleep(1);
	}

	close(fd);

    return 0;
}
