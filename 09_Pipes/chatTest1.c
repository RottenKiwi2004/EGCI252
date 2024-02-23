#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO "/tmp/fifo"

int main(int argc, char * argv[]) {

    if (access(FIFO, F_OK) == -1) // F_OK test if file exists
    {
        int res = mkfifo(FIFO, 0777); // make fifo pipe
        if (res)
        {
            fprintf(stderr, "Could not create fifo %s\n", FIFO);
            exit(EXIT_FAILURE);
        }
    }

    int res = open(FIFO, O_WRONLY); // Open for writing to pipe
    char buffer[512];
    while (strncmp(buffer, "end chat", 8))
    {
        int charCount = read(0, buffer, sizeof(buffer));
        write(res, buffer, charCount);
    }

}