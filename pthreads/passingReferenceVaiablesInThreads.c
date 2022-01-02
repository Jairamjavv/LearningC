#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

// create 10 threads, each taking a unique prime from the primes array and print it on the screen.

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* arg){
    int index = *(int*)arg;
    printf("%d ", primes[index]);
    free(arg);
}

int main(){
    
    pthread_t th[10];
    
    for(int i=0;i<10;i++){
        int* a =malloc(sizeof(int));
        *a=i;
        if(pthread_create(&th[i], NULL, &routine, a)!=0){
            perror("Failed to create thread");
        }
    }
    
    for(int i=0;i<10;i++){
        if(pthread_join(th[i], NULL)){
            perror("Failed to join thread");
        }
    }
    
    return 0;
}
