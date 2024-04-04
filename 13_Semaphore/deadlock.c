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

static int semaphoreP(int);
static int semaphoreV(int);

static int semID1, semID2;

void f1(pid_t);
void f2(pid_t);

void f1(pid_t pid) {
  printf("f1 called\n");
  semaphoreP(semID1);
  printf("f1 locked\n");

  if (pid)
    f2(pid);

  semaphoreV(semID1);
  printf("f1 unlocked\n");
}

void f2(pid_t pid) {
  printf("f2 called\n");
  semaphoreP(semID2);
  printf("f2 locked\n");

  if (!pid)
    f1(pid);

  semaphoreV(semID2);
  printf("f2 unlocked\n");
}

int main() {
  semID1 = semget((key_t)1234, 1, 0666 | IPC_CREAT);
  semID2 = semget((key_t)2345, 1, 0666 | IPC_CREAT);
  int pid = fork();
  if (pid) { // Parent Process
    f1(pid);

  } else {
    f2(pid);
  }
  printf("Done! %s\n", pid ? "Parent" : "Child");
}

static int semaphoreP(int semID) {

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

static int semaphoreV(int semID) {

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