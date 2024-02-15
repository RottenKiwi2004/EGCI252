#include <sys/types.h> // Data types
#include <signal.h> // Library for signal handling
#include <stdio.h>

void callback(int signo){
    printf("Signal received: %d\n", signo);
}

int main() {
    signal(SIGUSR1, callback);
    for(;;) pause();
}