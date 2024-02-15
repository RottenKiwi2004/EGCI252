#include <stdlib.h>
#include <stdio.h>

int main() {

	printf("Using system function for running ps program \n");
	system("ps -alx");
	printf("ps completed\n");
	return 0;

}
