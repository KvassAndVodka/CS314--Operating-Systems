// resource_preemtion.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void* thread1(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock1);
        sleep(1);

        // Trylock lock2, release lock1 and retry if failed
        if (pthread_mutex_trylock(&lock2) == 0) {
            printf("Thread 1 acquired both locks\n");
            pthread_mutex_unlock(&lock2);
            pthread_mutex_unlock(&lock1);
            break;
        }
        printf("Thread 1 releasing lock1 and retrying\n");
        pthread_mutex_unlock(&lock1);
        sleep(1); // Short delay before retrying
    }
    return NULL;
}

void* thread2(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock2);
        sleep(1);

        // Attempt to acquire lock1, otherwise release lock2 and retry
        if (pthread_mutex_trylock(&lock1) == 0) {
            printf("Thread 2 acquired both locks\n");
            pthread_mutex_unlock(&lock1);
            pthread_mutex_unlock(&lock2);
            break;
        } else {
            printf("Thread 2 releasing lock2 and retrying\n");
            pthread_mutex_unlock(&lock2);
            sleep(1); // Short delay before retrying
        }
    }
    return NULL;
}

int main(){
    pthread_t t1, t2;
    printf("Resolving Deadlock using Resource Preemption.\n");

    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    
    return 0;
    }