#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

// Sum of the numbers in the given primes array

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* arg){
    int index = *(int*)arg;
    int sum = 0;
    for(int i=0;i<index+5;i++){
        sum+=primes[index+i];
    }
    *(int*)arg = sum;
    return arg; // returning arg to pthread_join and there it will become result
}

int main(){
    
    pthread_t th[2];
    int sum=0;
    
    for(int i=0;i<2;i++){
        int* a = malloc(sizeof(int));
        *a=i*5;
        if(pthread_create(&th[i], NULL, &routine, a)!=0){ // passing a to routine and there it will be arg
            perror("Failed to create thread");
        }
    }
    
    for(int i=0;i<2;i++){
        int* result;
        if(pthread_join(th[i], (void**)&result) != 0){
            perror("Failed to join thread");
        }
        sum+=*result;
        free(result);
    }
    
    printf("%d", sum);
    
    return 0;
}
