#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{

	FILE *readFP; char buffer[BUFSIZ+1];
	int charsRead;
	memset(buffer, '\0', sizeof(buffer));
	readFP = popen("uname -a", "r");
	if (readFP != NULL)
	{
		charsRead = fread(buffer, sizeof(char), BUFSIZ, readFP);
		if(charsRead > 0)
			printf("Output from pipe:\n%s\n", buffer);
		pclose(readFP); exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);

}
