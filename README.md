# CA-Internship-Assignment
Counting with Threads  
Evan Branch

## **How to Run the Code**
Once you have navigated to the directory of the cloned repo in your terminal, run this compile command  
**Compile Command:** ```g++ -Wall main.cpp Thread.cpp -o counter_app -lpthread```  
Then, run the command  
**Run Command:** ```./counter_app```

## **How it Works, I used a Thread Wrapper class**  

1. **The Parent Class(```Thread```)**  
  This is an abstract base class that wraps the *pthread* library which allows the use and management of threads in C++. I used a proxy function and void pointer to allow the C based library to understand C++ objects.

2. **The Child Class(```CounterThread```)**  
   The ```CounterThread``` class inherits from the ```Thread``` parent class and adds the actual logic for counting. In this version, the threads are responsible for incrementing two separate counters at the same time. By overriding the ```run()``` function, each thread shows a "displayID", the specific counter we are incrementing, as well as the number it is currently on.

## **Logic FLow**  
1. ```main``` creates 5 "worker" threads.
2. **Dual-Counters**: I used two different mutexes for the counters. This allows the system to work dynamically, as one thread can lock Counter 1 without interfering with another threads ability to work on Counter 2.
3. **Display Lock**: I ran into a problem where sometimes a threads message would cut off another threads message mid-sentence. So, I implemented a third "Display Mutex" to make sure the output was clean.
4. Each thread runs in a loop, attempting to grab a counter's key, incrementing the value, printing the update while holding the display key, and then releasing both.
5. The main program waits for each thread to reach their "done" state, and then prints a message to indicate completion.

