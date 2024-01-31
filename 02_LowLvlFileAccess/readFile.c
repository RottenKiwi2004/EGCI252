#include <unistd.h>
int main(void)
{
	int bufferSize = 10;
	int nread; char buffer[bufferSize];
	nread = read(0, buffer, bufferSize);
	if (nread == -1) write(2, "An error has occurred\n", 21);
	else write(1, buffer, nread);
}
