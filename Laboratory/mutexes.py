import threading

lock = threading.Lock()
shared_resource = 0

def increment():
    global shared_resource
    with lock:
        shared_resource += 1
        print(f"Shared resource: {shared_resource}")
        
threads = []
for _ in range(10):
    thread = threading.Thread(target=increment)
    threads.append(thread)
    thread.start()
    
for thread in threads:
    thread.join()
    
