// to jest pierwszy plik
// pobiera argument z konsoli i przekazuje go do kolejnego programu
// uruchamiając go z parametrami obsługiwanymi przez get opt w 2 programie 

#include <stdio.h>
#include <unistd.h>

int main ()
{
	unsigned long int liczba;
	unsigned long int modulo;
	printf("wskaz liczbe z zakresu 11 do 999 \n");
	scanf("%li", &liczba);
	printf("wskazana liczba to %li\n", liczba);
	modulo = liczba % 10;
	printf("modulo liczba (10) to: %li\n", modulo);
	sleep(1);
	return 2;
}
