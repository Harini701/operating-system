#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t condition;
int instances = 4;

void wait_semaphore() {
    pthread_mutex_lock(&mutex);
    while (instances == 0) {
        pthread_cond_wait(&condition, &mutex);
    }
    instances--;
    pthread_mutex_unlock(&mutex);
}

void signal_semaphore() {
    pthread_mutex_lock(&mutex);
    instances++;
    pthread_cond_signal(&condition);
    pthread_mutex_unlock(&mutex);
}

void* process(void* arg) {
    char* thread_name = (char*)arg;
    printf("%s is waiting...\n", thread_name);
    wait_semaphore();
    printf("%s has acquired the resource.\n", thread_name);
    printf("%s is releasing the resource.\n", thread_name);
    signal_semaphore();
    return NULL;
}

int main() {
    pthread_t threads[5];
    char* thread_names[5] = {"P1", "P2", "P3", "P4", "P5"};

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condition, NULL);
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, process, (void*)thread_names[i]);
    }
    pthread_create(&threads[4], NULL, process, (void*)thread_names[4]);
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

    return 0;
}

