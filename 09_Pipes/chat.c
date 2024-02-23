#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

#define FIFO1_2 "./fifo1to2"
#define FIFO2_1 "./fifo2to1"

void endChatHandler(int signo) {
    if (signo == SIGTERM)
    {
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char * argv[]) {

    if (argc < 2)
    {
        printf("Please specify the client number\n");
        return 0;
    }
    int userNum = atoi(argv[1]);

    if (userNum < 1 || userNum > 2)
    {
        printf("Invalid client number\n");
        return 0;
    }

    if (access(FIFO1_2, F_OK) == -1) // F_OK test if file exists
    {
        if (mkfifo(FIFO1_2, 0777))
        {
            fprintf(stderr, "Could not create fifo %s\n", FIFO1_2);
            exit(EXIT_FAILURE);
        }
    }
    if (access(FIFO2_1, F_OK) == -1) // F_OK test if file exists
    {
        if (mkfifo(FIFO2_1, 0777))
        {
            fprintf(stderr, "Could not create fifo %s\n", FIFO2_1);
            exit(EXIT_FAILURE);
        }
    }


    if (userNum == 1)
    {
        int res;
        char buffer[8];
        pid_t pid = fork();
        signal(SIGTERM, endChatHandler);
        if (pid) // Parent
        {
            int res;
            char buffer[8];
            res = open(FIFO1_2, O_WRONLY); // Open for writing to pipe
            while (strncmp(buffer, "end chat", 8))
            {
                memset(buffer, 0, sizeof(buffer));
                int charCount = read(0, buffer, sizeof(buffer));
                // printf("buffer parent: %d", strncmp(buffer, "end chat", 8));
                write(res, buffer, charCount);
            }
            close(res);
            unlink(FIFO1_2);
            kill(pid, SIGTERM);
            raise(SIGTERM);
            // exit(EXIT_SUCCESS);
        }
        else // Child
        {
            signal(SIGTERM, endChatHandler);
            // int res;
            // char buffer[8];
            res = open(FIFO2_1, O_RDONLY); // Open for reading from pipe
            while (strncmp(buffer, "end chat", 8))
            {
                memset(buffer, 0, sizeof(buffer));
                int charCount = read(res, buffer, sizeof(buffer));
                // printf("buffer child: %d", strncmp(buffer, "end chat", 8));
                write(1, buffer, charCount);
            }
            printf("\n");
            close(res);
            unlink(FIFO2_1);
            kill(getppid(), SIGTERM);
            raise(SIGTERM);
            // exit(EXIT_SUCCESS);
        }
    }
    else
    {
        int res;
        char buffer[8];
        pid_t pid = fork();
        signal(SIGTERM, endChatHandler);
        if (pid) // Parent
        {
            res = open(FIFO2_1, O_WRONLY); // Open for writing to pipe
            while (strncmp(buffer, "end chat", 8))
            {
                memset(buffer, 0, sizeof(buffer));
                int charCount = read(0, buffer, sizeof(buffer));
                // printf("buffer parent: %d", strncmp(buffer, "end chat", 8));
                write(res, buffer, charCount);
            }
            close(res);
            unlink(FIFO2_1);
            kill(pid, SIGTERM);
            raise(SIGTERM);
            // exit(EXIT_SUCCESS);
        }
        else // Child
        {
            signal(SIGTERM, endChatHandler);
            // int res;
            // char buffer[8];
            res = open(FIFO1_2, O_RDONLY); // Open for reading from pipe
            while (strncmp(buffer, "end chat", 8))
            {
                memset(buffer, 0, sizeof(buffer));
                int charCount = read(res, buffer, sizeof(buffer));
                // printf("buffer child: %d", strncmp(buffer, "end chat", 8));
                write(1, buffer, charCount);
            }
            printf("\n");
            close(res);
            unlink(FIFO1_2);
            kill(getppid(), SIGTERM);
            raise(SIGTERM);
            // exit(EXIT_SUCCESS);
        }
    }

}