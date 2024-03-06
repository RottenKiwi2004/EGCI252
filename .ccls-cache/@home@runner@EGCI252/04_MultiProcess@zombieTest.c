#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
	int pid = fork();
	if (pid) { // Parent
		sleep(10);
		int status;
		int childPID = wait(&status);
		printf("childPID = %d, pid = %d, status = %d\n", childPID, pid, status);
	}
	else {
		sleep(2);
		printf("Child finished\n");
		return 10;
	}
}