#include "Thread.h"
#include <iostream>

Thread::Thread() {
  mThreadID = 0;
  mThreadFinished = false;
  mThreadRunning = false;
}

void Thread::start() {
 mThreadFinished = false;
 if(!mThreadRunning){
  mThreadRunning = true;
  pthread_create(&mThreadID, NULL, thread_proxy, this);
 }
}

bool Thread::done(){
  return mThreadFinished;
}

void Thread::stop() {
  if(mThreadRunning){
    pthread_cancel(mThreadID);
    mThreadRunning = false;
  }
}

void* Thread::thread_proxy(void* arg) {
  Thread* threadPointer = static_cast<Thread*>(arg);

  threadPointer->run();

  threadPointer->mThreadRunning = false;
  threadPointer->mThreadFinished = true;

  return nullptr;
}

Thread::~Thread(){
}
