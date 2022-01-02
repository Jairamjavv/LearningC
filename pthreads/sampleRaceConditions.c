#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

// Race condition

int mails = 0;

void* routine(){
    for(int i=0;i<10000000;i++)
        mails++;
    // read mails
    // increement mails=mails+1
    // write mails
}

int main(){
    
    pthread_t t1, t2;
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
    return 0;
}
