#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {

	pid_t pid;
	char * msg;
	int n;
	printf("Fork program starting\n");
	pid = fork();

	switch(pid) {
		case -1: _exit(1); // error
		case 0: msg = "Child!"; n = 5; break; // child created
		default: msg = "Parent"; n = 3; break; // parent created
	}

	for(; n>0; n--) {
		printf("%s: %d\n", msg, n);
		sleep(1);
	}

	if (pid) {
		int statVal; pid_t childPID;
		childPID = wait(&statVal);
		printf("Child has finished: PID = %d\n", childPID);
		if(WIFEXITED(statVal))
			printf("Child exited with code %d\n", WEXITSTATUS(statVal));
		else
			printf("Child termintated abnormally\n");
	} else{
    printf("parent process id is %d\n", getppid());
    printf("child process id is %d\n", getpid());
  }

	_exit(0);

}
