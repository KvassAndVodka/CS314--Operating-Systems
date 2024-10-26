#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;
sem_t empty_slots;
sem_t filled_slots;
pthread_mutex_t mutex;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&empty_slots);
        pthread_mutex_lock(&mutex);
        buffer[count++] = i;
        printf("Produce: %d\n", i);
        pthread_mutex_unlock(&mutex);
        sem_post(&filled_slots);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&filled_slots);
        pthread_mutex_lock(&mutex);
        int item = buffer[--count];
        printf("Consume: %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty_slots);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&filled_slots, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty_slots);
    sem_destroy(&filled_slots);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}