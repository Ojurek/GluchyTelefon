//2.	"Argument"
//◦	Wejście: argument do programu parsowany za pomocą getopt
//◦	Modyfikacja/wyjście: x:= Następna liczba pierwsza 


#include "2_argument.h"

int main(int argc, char* argv[]){

	uint32_t received;
	int fd;
	
	received = getopt(argc,argv,"0123456789")-'0';

 	printf("Program 2: orzymano liczbe: %i\n", received);

	received = next_prime_no(received);	
 	printf("Program 2: kolejna liczba pierwsza = %i\n", received);	

	fd = open(FIFO, O_WRONLY);
	if (fd < 0){
		printf("Program 2: nie udalo sie otworzyc FIFO");
		killpg(getpgid(getpid()),SIGINT);
 	}

	write(fd, &received, sizeof(uint32_t)); 

	close(fd);	
return 0;
}

int next_prime_no(int number){

	int prime = 0;

	if (number<3){
		return number+1;
	}

	number++;
	if ((number%2)==0){
		number++;
	}

	while (prime == 0){
		prime = 1;

		for (int i=3; i<number;i++){
			if ((number % i) == 0){
				prime = 0;
				break;
			}	
		}
	number+=2;
	}
 return number-2;
}
