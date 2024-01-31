#include <stdio.h>
#include <time.h>
#include<unistd.h>
#define clear() printf("\033[H\033[J")
int main ()
{
  while(1){
  	time_t rawtime;
  	struct tm * timeinfo;

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
	clear();
  	printf ("Current local time and date: %s", asctime (timeinfo) );
	sleep(1);
  }
  return 0;
}
