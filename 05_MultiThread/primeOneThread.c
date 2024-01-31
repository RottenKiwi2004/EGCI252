#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define maxThread 1
#define upperBound 50000

int primeListFromThread[maxThread][upperBound / maxThread] = {0};
int primeCountInThread[maxThread] = {0};

typedef struct findPrimeParam findPrimeParam;
struct findPrimeParam {
    int a; int b; int threadNum;
};

void addPrimeToList(int n, int threadNum) {
    primeListFromThread[threadNum][primeCountInThread[threadNum]++] = n;
}

void * findPrimeFrom(void * parameters) {
    findPrimeParam * param = (struct findPrimeParam *) parameters;
    int a = param->a, b = param->b, threadNum = param->threadNum;
    int i; for(i=a; i<=b; i++) {
        if (i < 2) continue;
        int maxPossibleFactor = sqrt(i) + 1;
        int isPrime = 1;
        int j; for(j=2; j<=maxPossibleFactor; j++)
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        if (isPrime || i == 2) addPrimeToList(i, threadNum);
    }
}

int main() {

    pthread_t threadID[maxThread];
    findPrimeParam primeParam[maxThread];
    int i; for(i=0; i<maxThread; i++) {
        primeParam[i].a = i * (upperBound / maxThread);
        primeParam[i].b = (i + 1) * upperBound / maxThread - 1;
        primeParam[i].threadNum = i;
        pthread_create(&threadID[i], NULL, &findPrimeFrom, &primeParam[i]);
    }
    for(i=0; i<maxThread; i++)
        pthread_join(threadID[i], NULL);

    for(i=0; i<maxThread; i++){
        int j; for(j=0; j<primeCountInThread[i]; j++)
            printf("%d ", primeListFromThread[i][j]);
    }

    printf("\n");
}