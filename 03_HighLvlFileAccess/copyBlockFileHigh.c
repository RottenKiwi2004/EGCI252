#include <stdio.h>

int main() {

	FILE *in, *out;
	in = fopen("file.in", "r");
	out = fopen("file.out", "w");
	char dataBuffer[512];
	while(fgets(dataBuffer, 512, in) != NULL) fputs(dataBuffer, out);

	return 0;

}
