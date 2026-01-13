#include <iostream>
#include <unistd.h>
#include "Thread.h"


const int gMAXCOUNT = 100;
int gCounter = 0;
pthread_mutex_t gMutexLock = PTHREAD_MUTEX_INITIALIZER;

//Inherits Thread Abstract class to adopt multithreading via mutex and counting logic
class CounterThread : public Thread {
  private:
    int mDisplayID;
  public:
    
    CounterThread(int id) : Thread(), mDisplayID(id) {};

    void run() override {
      while(gCounter < gMAXCOUNT){
        pthread_mutex_lock(&gMutexLock);

        if(gCounter < gMAXCOUNT){
          gCounter++;
          std::cout << "Thread " << mDisplayID << " set count to " << gCounter << ".\n";
        }

        pthread_mutex_unlock(&gMutexLock);

        usleep(10000);
      }
    }
};

/*
  Implements counting logic and distrubes the workload between 5 threads. 
  Threads dynamically claim the next number when available until gMAXCOUNT is met.
*/
int main(){
  CounterThread* counterThreadArray[5];

  
  for (int i = 0; i < 5; i++){
    counterThreadArray[i] = new CounterThread(i + 1);
    counterThreadArray[i]->start();
  }

  bool threadsComplete = false;
  while (!threadsComplete){
    threadsComplete = true;
    for (int i = 0; i < 5; i++){
      if (!counterThreadArray[i]->done()) {
        threadsComplete = false;
        break;
      }
    }
    usleep(1000);
  }

  std::cout << "All threads complete. We have counted to " << gMAXCOUNT << "!";
  

  return 0;
}

