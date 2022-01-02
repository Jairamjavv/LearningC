#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

// using mutex to solve Race condition
// NOTE: Race condition occures only multicore systems

int mails = 0;
pthread_mutex_t mutex; // creating a mutex variable

void* routine(){
    for(int i=0;i<10000000;i++){
        pthread_mutex_lock(&mutex); // locks the code mails++ from other threads executing it parallelly
        mails++;
        pthread_mutex_unlock(&mutex); // unlocks the code mails++ from other threads executing it parallelly
    }
    // read mails
    // increement mails=mails+1
    // write mails
}

int main(){
    
    
    pthread_t t1, t2;
    
    pthread_mutex_init(&mutex, NULL); // initializing a mutex
    if(pthread_create(&t1, NULL, &routine, NULL)){
        return 1;
    }    
    
    if(pthread_create(&t2, NULL, &routine, NULL)){
        return 2;
    }
    
    if(pthread_join(t1, NULL)){
        return 3;
    }
    
    if(pthread_join(t2, NULL)){
        return 4;
    }
    
    printf("The number of mails:%d\n", mails);
    printf("The number of mails unread:%d\n", 2*10000000-mails);
    // these unread data is because of race condition. when there are less mails, it was working fine, but when number of mails increases, complexity rises.
    pthread_mutex_destroy(&mutex); // destroys the memory allocated to mutex
    return 0;
}
