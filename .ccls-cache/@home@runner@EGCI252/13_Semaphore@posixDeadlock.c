#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

const int pauseTime = 800;

int main(int argc, char *argv[]) {
  sem_t *mySem = sem_open("/mySem", O_CREAT | O_RDWR, 0660, 1);
  char currentChar = 'O';
  if (argc > 1) {
    currentChar = 'X';
    usleep(pauseTime);
  }

  for (int i = 0; i < 10; i++) {
    if (sem_wait(mySem) == -1)
      exit(EXIT_FAILURE);

    // Begin critical section
    printf("%c", currentChar);
    fflush(stdout);
    usleep(pauseTime);
    printf("%c", currentChar);
    fflush(stdout);
    // End critical section

    if (sem_post(mySem) == -1)
      exit(EXIT_FAILURE);

    usleep(pauseTime);
  }

  printf("\n%d Finished\n", getpid());
  if (argc > 1) {
    usleep(pauseTime);
    sem_unlink("/mySem");
  }
  exit(EXIT_SUCCESS);
}