#include <stdio.h>

int main(void)
{

	printf("Real UID = %d, EffUID = %d\n", getuid(), geteuid());
	return 0;

}
