#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

sem_t wrt;
pthread_t tid;
int readercount = 0;
pthread_mutex_t mutex;

void *reader(void* param)
{
    pthread_mutex_lock(&mutex);
    readercount++;
    if(readercount==1)
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);
    printf("Reader %d Entered\n",readercount);
    sleep(1);
    pthread_mutex_lock(&mutex);
    readercount--;
    if(readercount==0)
    {
        sem_post(&wrt);
    }
    printf("Reader %d Left\n",readercount+1);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *writer(void* param)
{
    printf("Writer Not Entered\n");
    sem_wait(&wrt);
    printf("Writer Entered\n");
    sem_post(&wrt);
    printf("Writer Left\n");
    return NULL;
}

int main()
{
    int noOfReaders,i;
    scanf("%d",&noOfReaders);
    printf("\n");
    int n1[noOfReaders];
    sem_init(&wrt,0,1);
    
    pthread_t writerthreads,readerthreads[noOfReaders];
    
    for(i=0;i<noOfReaders;i++)
    {
        pthread_create(&writerthreads,NULL,writer,NULL);
        pthread_create(&readerthreads[i],NULL,reader,NULL);
    }
    for(i=0;i<noOfReaders;i++)
    {
        pthread_join(writerthreads,NULL);
        pthread_join(readerthreads[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
}
