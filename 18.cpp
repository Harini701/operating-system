#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define BUFFER_SIZE 3

int buffer[BUFFER_SIZE];
int buffer_count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int i;
    for (i = 1; i <= 4; i++) {
        pthread_mutex_lock(&mutex);
        while (buffer_count == BUFFER_SIZE) {
            printf("Buffer is full. Waiting for consumer to consume.\n");
            pthread_cond_wait(&full, &mutex);
        }
        buffer[in] = i;
        in = (in + 1) % BUFFER_SIZE;
        buffer_count++;
        printf("Produced %d\n", i);
        if (buffer_count == 1) {
            pthread_cond_signal(&empty);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg) {
    pthread_mutex_lock(&mutex);
    while (buffer_count == 0) {
        printf("Buffer is empty. Waiting for producer to produce.\n");
        pthread_cond_wait(&empty, &mutex);
    }
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    buffer_count--;
    printf("Consumed %d\n", item);
    if (buffer_count == BUFFER_SIZE - 1) {
        pthread_cond_signal(&full);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}

