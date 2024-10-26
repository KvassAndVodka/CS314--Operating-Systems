#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
int shared_resource = 0;

void* increment(void* arg) {
    pthread_mutex_lock(&lock);
    shared_resource++;
    printf("Shared resource: %d\n", shared_resource);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[10];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}