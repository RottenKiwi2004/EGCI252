#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void)
{

	char buffer[512];
	char nullString[16];
	int i;
	for (i=0;i<16;i++) nullString[i] = '\0';
	int in = open("hole.in", O_RDONLY);
	int out = open("hole.out", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	int nread, total = 0;
	while ( (nread = read(in, buffer, sizeof(buffer)) ) > 0) {
		write(out, buffer, nread);
		total += nread;
	}
	
	int nullStartPos = total / 2 - 8;
	
	lseek(out, nullStartPos, SEEK_SET);
	write(out, nullString, 16);
}
