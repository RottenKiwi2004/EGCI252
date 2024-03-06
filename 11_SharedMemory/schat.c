#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

#define MEMSIZE 4096

void signalHandler(int signo) {
	if (signo == SIGTERM) exit(EXIT_SUCCESS);
}

struct SharedStructure {
	int written1;
	char data1[BUFSIZ];
	int written2;
	char data2[BUFSIZ];
};

int main(int argc, char * argv[]) {

	int client = atoi(argv[1]);
	signal(SIGTERM, signalHandler);
	int pid = fork();
	
	// Get or create shared memory ID
	int sharedID;
	sharedID = shmget((key_t)6481328, sizeof(struct SharedStructure), 0666 | IPC_CREAT);
	if (sharedID == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// Match the memory
	void * sharedMemory = shmat(sharedID, NULL, 0);
	if (sharedMemory == (void *) -1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	// Cast to struct type
	struct SharedStructure * sharedArea = (struct SharedStructure *) sharedMemory;

	
	
	// Parent
	if (pid) {
		// Client 1
		if (client == 1) {
			char buffer[BUFSIZ];
			// Write loop
			while (1) {
				while(sharedArea->written1 == 1) {sleep(1); printf("Sending...\n");}
				printf("Enter data: ");
				memset(sharedArea->data1, 0, sizeof(sharedArea->data1));
				fgets(sharedArea->data1+1, BUFSIZ, stdin);
				strcpy(buffer, sharedArea->data1+1);
				sharedArea->written1 = 1;
				// char * b = buffer;
				// printf("0%c1%c2%c3%c4%c5%c6%c7%c8%c\n", b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8]);
				if (strncmp(buffer, "end chat", 8) == 0) {
					// printf("End chat triggered in parent\n");
					break;
				}
			} // End write loop
			// printf("Out of loop\n");
			kill(pid, SIGTERM);
		} // End Client 1



		// Client 2
		if (client == 2) {
			char buffer[BUFSIZ];
			// Write loop
			while (1) {
				while(sharedArea->written2 == 1) { printf("Sending...\n"); sleep(1); }
				printf("Enter data: ");
				memset(sharedArea->data2, 0, sizeof(sharedArea->data2));
				fgets(sharedArea->data2+1, BUFSIZ, stdin);
				strcpy(buffer, sharedArea->data2+1);
				sharedArea->written2 = 1;
				if (strncmp(buffer, "end chat", 8) == 0) {
					// printf("End chat triggered in parent\n");
					break;
				}
			} // End write loop
			kill(pid, SIGTERM);
		} // End Client 2
		
	}

		
	// Child
	else {
		// Client 1
		if (client == 1) {
			// Read loop
			while (1) {
				// There's something to read
				if (sharedArea->written2 == 1) {
					printf("%s", sharedArea->data2+1);
					sharedArea->written2 = 0;
					if (strncmp(sharedArea->data2+1, "end chat", 8) == 0) {
						// printf("End chat triggered in chlid\n");
						break;
					}
				}
				usleep(500000);
			}
			kill(getppid(), SIGTERM);
		} // End Client 1
		
		// Client 2
		if (client == 2) {
			// Read loop
			while (1) {
				// There's something to read
				if (sharedArea->written1 == 1) {
					// char * b = sharedArea->data1;
					// printf("%p, 0%c1%c2%c3%c4%c\n", sharedArea->data1, b[0], b[1], b[2], b[3], b[4]);
					printf("%s", sharedArea->data1+1);
					sharedArea->written1 = 0;
					if (strncmp(sharedArea->data1+1, "end chat", 8) == 0) {
						// printf("End chat triggered in chlid\n");
						break;
					}
				}
				usleep(500000);
			}
			kill(getppid(), SIGTERM);
		} // End Client 2
	}


	
}