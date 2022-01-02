#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TOTAL_ITEMS 4
#define FULL 0
#define EMPTY 0
int* buffer;
int nextIn = 0;
int nextOut = 0;

sem_t empty_sem_mutex;
sem_t full_sem_mutex; 
pthread_mutex_t mutex;


void * Producer(void* bufferSize)
{
  int i;
  
  for(i = 0; i < TOTAL_ITEMS; i++)
    {
        int item = rand()%100;
        sem_wait(&empty_sem_mutex); 
        pthread_mutex_lock(&mutex);
        buffer[nextIn] = item;
        nextIn = (nextIn + 1) % *(int*)bufferSize;
        printf("Producing %d\n",item);
        pthread_mutex_unlock(&mutex);
        sem_post(&full_sem_mutex);
    }
}

void * Consumer(void* bufferSize)
{
  for(int i = 0; i < TOTAL_ITEMS; i++)
    {
        sem_wait(&full_sem_mutex); 
        pthread_mutex_lock(&mutex);
        int item = buffer[nextOut];
        nextOut = (nextOut + 1) % *(int*)bufferSize;
        printf("\tConsuming %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty_sem_mutex);
    }
}

int main()
{    
    int bufferSize;
    int noOfProdCons=3;
    scanf("%d", &bufferSize);
    
    pthread_t prod,cons;
    srand(time(NULL));
    buffer = malloc(sizeof(int*)*bufferSize);
    
    sem_init(&empty_sem_mutex,0,bufferSize);
    sem_init(&full_sem_mutex,0,0);
    
    for(int i=0;i<noOfProdCons;i++){
    if(pthread_create(&prod, NULL,&Producer, &bufferSize))
    {
      perror("\n ERROR creating thread 1");
    }
    
    if(pthread_create(&cons, NULL,&Consumer, &bufferSize))
    {
      perror("\n ERROR creating thread 2");
    }
    
    if(pthread_join(prod, NULL)) // wait for the producer to finish
    {
      perror("\n ERROR joining thread");
    }
    
    if(pthread_join(cons, NULL)) // wait for consumer to finish
    {
      perror("\n ERROR joining thread");
    }
    }
    pthread_mutex_destroy(&full_sem_mutex);
    sem_destroy(&empty_sem_mutex);
    sem_destroy(&full_sem_mutex);
    
    pthread_exit(NULL);
    return 1;
}
