#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

// showing difference between thread and proess. 

// int main()
// {
//     int z=1;
    
//     int pid=fork();
//     if(pid == -1){
//         return 1;
//     }
//     // printf("Process Id%d\n", getpid());
//     if(pid==0){
//         z+=10;
//     }
//     sleep(3);
//     printf("The Value of Z:%d when pid is:%d\n", z, getpid());
//     if(pid != 0){
//         wait(NULL); // wait till child process completes its execution
//     }
//     return 0;
// }


//threads share memory
int x=2;

void* routine(){
    // printf("From threads with processs Id%d\n", getpid());
    x+=10;
    sleep(3);
    printf("The value of X is:%d\n", x);
}

void* routine2(){
    // printf("From threads with processs Id%d\n", getpid());
    printf("The value of X is:%d\n", x);
}

int main(){
        pthread_t thread1; // creating a thread variable
    if(pthread_create(&thread1, NULL, &routine, NULL)){
        return 1;
    } //Passing the thread variable, then passing the function and since it has no arguments we pass NULL
    
    if(pthread_join(thread1, NULL)){
        return 2;
    } // this acts like a wait but for threads, NULL is the output of the function, since out function return nothing we have passed NULL
    
            pthread_t thread2; // creating a thread variable
    if(pthread_create(&thread2, NULL, &routine2, NULL)){
        return 1;
    } //Passing the thread variable, then passing the function and since it has no arguments we pass NULL
    
    if(pthread_join(thread2, NULL)){
        return 2;
    }
}
