#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

void* roll_dice(){
    int value = (rand()%6)+1; // generating random value between 1 to 6
    int* result = malloc(sizeof(int)); // creating a dynamic allocation for result
    *result=value; // dynamic allocating the result value
    // printf("%d", value);
    return (void*) result;
}

int main(){
    int* res;
    
    srand(time(NULL)); // seed the random generrator with seed value as given and time as NULL
    
    pthread_t th;
    
    if(pthread_create(&th, NULL, &roll_dice, NULL) != 0){
        return 1;
    }
    if(pthread_join(th, (void**) &res) != 0){ // passing the reference of result as the pthread_join takes the argument as double pointer. 
                                    // Also typecast it to void** in order to avoid warnings
        return 2; 
    }
    
    printf("%d" , *res);
    free(res);
    return 0;
}
