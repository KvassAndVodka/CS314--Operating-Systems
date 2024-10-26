// simulating_deadlock.c
// This program demonstrates a potential deadlock situation in multithreading.

#include <stdio.h>      // For standard input-output functions
#include <pthread.h>    // For POSIX thread functions
#include <unistd.h>     // For sleep function

// Declare two mutex locks to simulate resource locking
pthread_mutex_t lock1;
pthread_mutex_t lock2;

// Thread function for thread1
void* thread1(void* arg) {
    pthread_mutex_lock(&lock1);     // Lock lock1 first
    sleep(1);                       // Simulate process time
    pthread_mutex_lock(&lock2);     // Lock lock2
    printf("Thread 1 acquired both locks\n");
    pthread_mutex_unlock(&lock2);   // Release lock2
    pthread_mutex_unlock(&lock1);   // Release lock1
    return NULL;
}

void* thread2(void* arg) {
    pthread_mutex_lock(&lock2);     // Lock lock2 first
    sleep(1);                       // Simulate process time
    pthread_mutex_lock(&lock1);     // Lock lock1
    printf("Thread 2 acquired both locks\n");
    pthread_mutex_unlock(&lock1);   // Release lock1
    pthread_mutex_unlock(&lock2);   // Release lock2
    return NULL;
}

int main() {
    pthread_t t1, t2;  // Declare two threads

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
