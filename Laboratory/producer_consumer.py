import threading
import queue

buffer = queue.Queue(maxsize=5)

def producer():
    for i in range(10):
        buffer.put(i)
        print(f"Produce: {i}")

def consumer():
    for _ in range(10):
        item = buffer.get()
        print(f"Consume: {item}")

prod_thread = threading.Thread(target=producer)
cons_thread = threading.Thread(target=consumer)

prod_thread.start()
cons_thread.start()

prod_thread.join()
cons_thread.join()