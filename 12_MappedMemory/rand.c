#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

#define FILE_LENGTH 0x100
int RDEV;

int randRange(unsigned const low, unsigned const high) {
	printf("Test\n");
	unsigned const range = high - low + 1;
	unsigned int randNum;
	read(RDEV, &randNum, sizeof(randNum));
	return low + (int)((double)range * randNum / (UINT_MAX + 1.0));
}

int main(int argc, char *argv[])
{
	int fd;
	void * fileMemory;
	// srand(time(NULL));
	RDEV = open("/dev/urandom", O_RDONLY);

	fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	lseek(fd, FILE_LENGTH + 1, SEEK_SET);
	write(fd, "", 1);
	lseek(fd, 0, SEEK_SET);

	fileMemory = mmap(0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);

	sprintf((char *)fileMemory, "%d", randRange(-100, 100));

	munmap(fileMemory, FILE_LENGTH);
	return 0;

}