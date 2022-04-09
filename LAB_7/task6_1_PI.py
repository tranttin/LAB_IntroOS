import random
import math
import threading
counter = 0
seed = 1000000

def thread_task(lock):
  global counter
  for i in range(seed):
    x=random.random()
    y=random.random()
    dist = math.sqrt (x*x + y * y)
    if (dist < 1.0): 
      counter=counter+1;

def main():
  # creating a lock
  lock = threading.Lock()
  
  t1 = threading.Thread(target=thread_task, args=(lock,))
  t2 = threading.Thread(target=thread_task, args=(lock,))

  # start threads
  t1.start()
  t2.start()

  # wait until threads finish their job
  t1.join()
  t2.join()
  PI = counter/(seed*2)*4
  print(PI)

main()
