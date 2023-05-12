#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
sem_t semaphore;
int shared_data;

void *thread1(void *arg) {
    sem_wait(&semaphore); 
    int data = shared_data;
    shared_data *= 2; 
    printf("Thread 1: read %d, wrote %d\n", data, shared_data);
    sem_post(&semaphore);
    return NULL;
}

void *thread2(void *arg) {
    sem_wait(&semaphore); 
    int data = shared_data;
    shared_data *= 5; 
    printf("Thread 2: read %d, wrote %d\n", data, shared_data);
    sem_post(&semaphore);
    return NULL;
}

int main() {
    sem_init(&semaphore, 0, 1); 
    shared_data = 10;

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&semaphore); 
    return 0;
}

