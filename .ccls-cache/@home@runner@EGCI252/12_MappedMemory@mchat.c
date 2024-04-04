#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define FILE_LENGTH 0x10000

int main(int argc, char *argv[])
{
	int client = atoi(argv[1]);
	int pid = fork();
	int fd = open("chat_log", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	lseek(fd, FILE_LENGTH + 1, SEEK_SET);
	write(fd, "", 1);
	lseek(fd, 0, SEEK_SET);
	void * fileMemory = mmap(0, FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	
// Parent
if (pid)
{
	// Client 1
	if (client == 1)
	{
		int written; char * msg[BUFSIZ];
		fgets(msg, BUFSIZ, stdin);
		
	}
}

// Child
else {
	// Client 1
	if (client == 1)
	{
		int written; char * msg[BUFSIZ];
	}
}

	
}