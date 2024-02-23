#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	char buffer[BUFSIZ+1];
	sprintf(buffer, "This is a message for writing to a process!\n");
	FILE * writeFP = popen("od -c", "w");
	if (writeFP != NULL)
	{
		fwrite(buffer, sizeof(char), strlen(buffer), writeFP);
		pclose(writeFP); exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);

}
