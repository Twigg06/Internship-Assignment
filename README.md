# CA-Internship-Assignment
Counting with Threads  
Evan Branch

## **How to Run the Code**
Once you have navigated to the directory of the cloned repo in your terminal, run this compile command  
**Compile Command:** ```g++ -Wall main.cpp Thread.cpp -o counter_app -lpthread```  
Then, run the command  
**Run Command:** ```./counter_app```

## **How it Works**  
In this project, I used a **Thread Wrapper** class  

1. **The Parent Class(```Thread```)**  
  This is an abstract base class that wraps the *pthread* library which allows the use and management of threads in C++. I used a proxy function and void pointer to allow the C based library to understand C++ objects.

2. **The Child Class(```CounterThread```)**  
   The ```CounterThread``` class inherits from the ```Thread``` parent class and adds the actual logic for counting with each thread. By overriding the ```run()``` function, each thread shows a "displayID" as well as the number it is currently on.

## **Logic FLow**  
1. ```main``` creates 5 "worker" threads.
2. Each thread is contained in a loop, constantly trying to grab the mutex key.
3. Once a thread obtains the key, it increments the count, prints the number, and then releases the key.
4. The main program waits for each thread to reach their "done" state and prints a messaage to indicate such.

