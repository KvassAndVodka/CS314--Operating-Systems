import threading

semaphore = threading.Semaphore()
shared_resource = 0

def access_resource():
    global shared_resource
    with semaphore:
        shared_resource += 1
        print(f"Shared resource: {shared_resource}")

threads = []
for _ in range(10):
    thread = threading.Thread(target =  access_resource)
    threads.append(thread)
    thread.start()
    
for thread in threads:
    thread.join()