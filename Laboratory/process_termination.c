// process_termination.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void* thread1(void* arg) {
    pthread_mutex_lock(&lock1);
    sleep(1);

    if (pthread_mutex_trylock(&lock2) == 0) { // lock 2 available?
        printf("Thread 1 acquired both locks\n");
        pthread_mutex_unlock(&lock2);
    } else {
        printf("Thread 1 timed out on lock2 and will exit\n");
    }

    pthread_mutex_unlock(&lock1);
    return NULL;
}

void* thread2(void* arg) {
    pthread_mutex_lock(&lock2);
    sleep(1);

    if (pthread_mutex_trylock(&lock1) == 0) { // lock1 available?
        printf("Thread 2 acquired both locks\n");
        pthread_mutex_unlock(&lock1);
    } else {
        printf("Thread 2 timed out on lock1 and will exit\n");
    }

    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main(){
    pthread_t t1, t2;
    printf("Resolving Deadlock using Process Termination.\n");

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