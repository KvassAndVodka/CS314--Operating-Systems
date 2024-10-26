// simulating_deadlock.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Declare two mutex locks
pthread_mutex_t lock1;
pthread_mutex_t lock2;

// Thread function for thread1
void* thread1(void* arg) {
    // Lock lock1 first
    pthread_mutex_lock(&lock1);
    sleep(1);
    // Lock lock2
    pthread_mutex_lock(&lock2);
    printf("Thread 1 acquired both locks\n");
    // Release lock2
    pthread_mutex_unlock(&lock2);
    // Release lock1
    pthread_mutex_unlock(&lock1);
    return NULL;
}

// Thread function for thread2
void* thread2(void* arg) {
    // Lock lock2 first
    pthread_mutex_lock(&lock2);
    sleep(1);
    // Lock lock1
    pthread_mutex_lock(&lock1);
    printf("Thread 2 acquired both locks\n");
    // Release lock1
    pthread_mutex_unlock(&lock1);
    // Release lock2
    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main(){
    // Declare two threads
    pthread_t t1, t2;
    // Initialize both mutex locks
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    // Create thread1 and thread2, each executing their respective functions
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    // Wait for both threads to finish execution
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy the mutex locks after threads complete
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    
    return 0;
    }
