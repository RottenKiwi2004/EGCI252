#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MEMSIZE 4096

struct SharedStructure {
	int written1;
	char data1[BUFSIZ];
	int written2;
	char data2[BUFSIZ];
};

int main() {
	int runnning = 1, sharedID;
	void *sharedMemory = NULL;
	struct SharedStructure *sharedArea;
	sharedID = shmget((key_t)1234, sizeof(struct SharedStructure), 0666 | IPC_CREAT);
	if (sharedID == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
	sharedMemory = shmat(sharedID, NULL, 0);
	if (sharedMemory == (void *) -1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n", (int) sharedMemory);
	sharedArea = (struct SharedStructure *) sharedMemory;
	sharedArea->written1 = 0;
	
}