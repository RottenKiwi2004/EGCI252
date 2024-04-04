#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_NAME "/pshm"
#define MEM_SIZE 64

struct shmStruct {
  int written;
  char data[MEM_SIZE];
};

int main() {
  int shmfd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0660);
  if (shmfd == -1) {
    perror("shm_open failed");
    exit(EXIT_FAILURE);
  }

  int structSize = sizeof(struct shmStruct);
  ftruncate(shmfd, structSize);
  void *shMem =
      mmap(0, structSize, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
  printf("Memory attached at %p\n", shMem);
  struct shmStruct *sharedArea = (struct shmStruct *)shMem;
  sharedArea->written = 0;

  int running = 1;
  while (running) {
    if (sharedArea->written) {
      printf("Data written in shared memory: %s", sharedArea->data);
      sharedArea->written = 0;
      if (strncmp(sharedArea->data, "end", 3) == 0)
        running = 0;
    }
    usleep(200);
  }

  munmap(shMem, structSize);
  close(shmfd);

  if (shm_unlink(SHM_NAME) == -1) {
    perror("shm_unlink failed");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}