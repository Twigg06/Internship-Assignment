#include <iostream>
#include <unistd.h>
#include "Thread.h"


const int gMAXCOUNT = 100;

int gCounterOne = 0;
int gCounterTwo = 0;

pthread_mutex_t gMutexLockOne = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t gMutexLockTwo = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t gDisplayLock = PTHREAD_MUTEX_INITIALIZER;


//Inherits Thread Abstract class to adopt multithreading via mutex and counting lo
class CounterThread : public Thread {
  private:
    int mDisplayID;
  public:
    
    CounterThread(int id) : Thread(), mDisplayID(id) {};

    void run() override {
      while(gCounterOne < gMAXCOUNT || gCounterTwo < gMAXCOUNT){

        pthread_mutex_lock(&gMutexLockOne);
        if(gCounterOne < gMAXCOUNT){
          gCounterOne++;

          pthread_mutex_lock(&gDisplayLock);
          std::cout << "Thread " << mDisplayID << " set Counter 1 to " << gCounterOne << "." << std::endl;
          pthread_mutex_unlock(&gDisplayLock);

          pthread_mutex_unlock(&gMutexLockOne);
        }else{
          pthread_mutex_unlock(&gMutexLockOne);
        }

        pthread_mutex_lock(&gMutexLockTwo);
        if(gCounterTwo < gMAXCOUNT){
          gCounterTwo++;

          pthread_mutex_lock(&gDisplayLock);
          std::cout << "Thread " << mDisplayID << " set Counter 2 to " << gCounterTwo << "." << std::endl;
          pthread_mutex_unlock(&gDisplayLock);

          pthread_mutex_unlock(&gMutexLockTwo);
        }else{
          pthread_mutex_unlock(&gMutexLockTwo);
        }

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

  std::cout << "All threads complete. Each counter has counted to " << gMAXCOUNT << "!";
  

  return 0;
}

