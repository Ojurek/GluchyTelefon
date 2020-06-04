#ifndef _definition
#define _definition


#define FIFO "/tmp/myfifo"

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







#endif //_definition
