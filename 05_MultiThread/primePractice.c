#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct threadParam {
	int start;
	int end;
};

void * computePrime(void * tempParam) {
	struct threadParam * param = (struct threadParam *) tempParam;
	int * primeList = malloc(sizeof(int) * (param->end - param->start));
	printf("Prime list: %p\n", primeList);
	int idx = 0; memset(primeList, 0, sizeof(int) * (param->end - param->start));
	for (int i=param->start; i<=param->end; i++) {
		int isPrime = 1;
		for (int j=2; j<sqrt(i) + 1; j++)
			isPrime = isPrime && (i % j);
		if (isPrime && i > 2 || i == 2)
			primeList[idx++] = i;
	}

	// for(int i=0; i<idx; i++) printf("%d ", primeList[i]);
	pthread_exit((void *) primeList);
}

int main() {
	int threadNum = 5;
	pthread_t threadID[threadNum];
	for(int i=0; i<threadNum; i++) {
		// printf("%d ", i);
		struct threadParam temp;
		temp.start = i * 10000; temp.end = temp.start + 9999;
		pthread_create(&threadID[i], NULL, &computePrime, &temp);
	}
	int * primeList[threadNum];
	for(int i=0; i<threadNum; i++) {
		pthread_join(threadID[i], (void **) (primeList + i));
		printf("Prime list (main %d): %p\n", i, primeList[i]);
		// for(int j=0; primeList[i][j]; j++) printf("%d ", primeList[i][j]);
		// free(primeList[i]);
	}
	printf("%d\n", primeList[0][0]);
	printf("%d\n", primeList[1][0]);
	printf("%d\n", primeList[2][0]);
	printf("%d\n", primeList[3][0]);
	printf("%d\n", primeList[4][0]);
}