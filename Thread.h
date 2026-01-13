#pragma once
#include <pthread.h>

class Thread{
  private:
    pthread_t mThreadID;
    bool mThreadFinished;
    bool mThreadRunning;
  
  public:
    Thread();
    virtual ~Thread();
    
    void start();

    void stop();

    bool done();

    pthread_t id(){
      return this->mThreadID;
    }

    virtual void run() = 0;
    static void* thread_proxy(void* arg);
};