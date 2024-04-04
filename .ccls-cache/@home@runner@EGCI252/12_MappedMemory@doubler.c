#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#define FILE_LENGTH 0x100

int main(int argc, char * argv[])
{
	int fd = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
	void * fileMemory = mmap(0, FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	int n;
	sscanf(fileMemory, "%d", &n);
	
	printf("Value: %d\n", n);
	// lseek(fd, 0, SEEK_SET);
	sprintf((char *) fileMemory, "%d", n * 2);
	munmap(fileMemory, FILE_LENGTH);
	return 0;
}