# simulating_deadlock.py
import threading
import time

# Initialize two locks
lock1 = threading.Lock()
lock2 = threading.Lock()

def thread1():
    # Acquire the first lock
    with lock1:
        # Simulate some processing
        time.sleep(1)
        # Attempt to acquire the second lock
        with lock2:
            print("Thread 1 acquired both locks")

def thread2():
    # Acquire the second lock
    with lock2:
        # Simulate some processing
        time.sleep(1)
        # Attempt to acquire the first lock
        with lock1:
            print("Thread 2 acquired both locks")

# Create thread objects targeting the functions
t1 = threading.Thread(target=thread1)
t2 = threading.Thread(target=thread2)

# Start the threads
t1.start()
t2.start()

# Wait for both threads to complete
t1.join()
t2.join()
