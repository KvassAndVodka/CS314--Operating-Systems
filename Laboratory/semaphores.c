#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;
int shared_resource = 0;

void* access_resource(void* arg) {
    sem_wait(&semaphore);
    shared_resource++;
    printf("Shared resource: %d\n", shared_resource);
    sem_post(&semaphore);
    return NULL;
}

int main() {
    pthread_t threads[10];
    sem_init(&semaphore, 0, 1);

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, access_resource, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);
    return 0;
}