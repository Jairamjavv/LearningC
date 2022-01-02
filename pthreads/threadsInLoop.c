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
    
    
    pthread_t ths[3];

    
    pthread_mutex_init(&mutex, NULL); // initializing a mutex
    
    for(int i=0;i<3;i++){
        if(pthread_create(&ths[i], NULL, &routine, NULL)!=0){
            perror("failed to Create thread\n");
            return 1;
        }
    }
    for(int i=0;i<3;i++){
        if(pthread_join(ths[i], NULL)){
            return 2;
        }        
    }
    
    printf("The number of mails:%d\n", mails);
    printf("The number of mails unread:%d\n", 3*10000000-mails);
    // these unread data is because of race condition. when there are less mails, it was working fine, but when number of mails increases, complexity rises.
    pthread_mutex_destroy(&mutex); // destroys the memory allocated to mutex
    return 0;
}
