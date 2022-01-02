#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void* routine(){
    printf("Test from routine\n");
    sleep(3);
    printf("Ending Thread\n");
}

int main()
{
    pthread_t thread1; // creating a thread variable
    pthread_t thread2;
    // pthread_create returns some int value, On success, the return value is 0, and on failure, the return value is a nonzero value indicating the type of error.
    if(pthread_create(&thread2, NULL, &routine, NULL) == 0){ 
        printf("Safe threading:)\n");
    }
    else{
        printf("Linux systems bug you, unsafe threading\n");
    }
    pthread_create(&thread1, NULL, &routine, NULL); //Passing the thread variable, then passing the function and since it has no arguments we pass NULL
    
    pthread_join(thread1, NULL); // this acts like a wait but for threads, NULL is the output of the function, since out function return nothing we have passed NULL
    pthread_join(thread2, NULL);

    return 0;
}
