#include <stdio.h>

int main() {

	FILE *in, *out;
	in = fopen("file.in", "r");
	out = fopen("file.out", "w");
	char bufferChar;
	while((bufferChar = fgetc(in)) != EOF) putc(bufferChar, out);

	return 0;

}
