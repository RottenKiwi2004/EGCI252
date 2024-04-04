#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
};

static int setSemValue(void);
static void delSemValue(void);
static int semaphoreP(void);
static int semaphoreV(void);

static int semID;

int main(int argc, char *argv[]) {
  srand((unsigned int)getpid());
  semID = semget((key_t)1234, 1, 0666 | IPC_CREAT);

  char opChar = 'O';
  if (argc > 1) {
    if (!setSemValue()) {
      fprintf(stderr, "Failed to initialize semaphore\n");
      exit(EXIT_FAILURE);
    }
    opChar = 'X';
    sleep(2);
  }

  for (int i = 0; i < 10; i++) {

    // Starting critical section...
    // if (!semaphoreP())
    //   exit(EXIT_FAILURE);

    printf("%c", opChar);
    fflush(stdout);
    sleep(rand() % 3);
    printf("%c", opChar);
    fflush(stdout);

    // Finished critical section
    // if (!semaphoreV())
    //   exit(EXIT_FAILURE);

    sleep(rand() % 2);
  }

  printf("\n%d Finished\n", getpid());
  if (argc > 1) {
    sleep(10);
    delSemValue();
  }

  exit(EXIT_SUCCESS);
}

static int setSemValue(void) {
  union semun semUnion;
  semUnion.val = 1;
  if (semctl(semID, 0, SETVAL, semUnion) == -1)
    return 0;
  return 1;
}

static void delSemValue(void) {
  union semun semUnion;
  if (semctl(semID, 0, IPC_RMID, semUnion) == -1)
    fprintf(stderr, "Failed to delete semaphore\n");
}

static int semaphoreP(void) {

  struct sembuf semB;
  semB.sem_num = 0;
  semB.sem_op = -1;
  semB.sem_flg = SEM_UNDO;

  if (semop(semID, &semB, 1) == -1) {
    fprintf(stderr, "semaphoreP failed\n");
    return 0;
  }

  return 1;
}

static int semaphoreV(void) {

  struct sembuf semB;
  semB.sem_num = 0;
  semB.sem_op = 1;
  semB.sem_flg = SEM_UNDO;

  if (semop(semID, &semB, 1) == -1) {
    fprintf(stderr, "semaphoreV failed\n");
    return 0;
  }

  return 1;
}