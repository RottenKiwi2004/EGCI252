#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void myAlarm(int sig)
{ int i; for(i=0; i<5; i++) printf("Alarm!!!\n"); }

int main(void)
{

	int pid;
	printf("Alarm clock is starting...\n");

	if ((pid = fork()) == 0)
	{ sleep(3); kill(getppid(), SIGALRM); exit(0); }

	printf("Waiting for alarm... \n");
	(void) signal(SIGALRM, myAlarm);
	pause(); printf("Done!\n"); exit(0);

}
