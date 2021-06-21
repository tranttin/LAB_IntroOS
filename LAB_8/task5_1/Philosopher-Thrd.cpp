//------------------------------------------------------------------------
// Filename: 
//     Philosopher-Thrd.cpp
// PROGRAM DISCRIPTION
//     Philosopher thread class implementation file
//------------------------------------------------------------------------

#include <iostream.h>
#include <stdlib.h>
#include "ThreadClass.h"
#include "Philosopher-Thrd.h"
#include "Philosopher-mon.h"

// the monitor that manage the distribution of chopsticks

static PhilosopherMonitor PhilMonitor("PhilosopherMonitor");     

// -----------------------------------------------------------------------
// FUNCTION  Filler():                                              
//    This function fills a strstream with spaces.                 
// -----------------------------------------------------------------------

strstream *Filler(int n)
{
     int  i;
     strstream *Space;

     Space = new strstream;
     for (i = 0; i < n; i++)
          (*Space) << ' ';
     (*Space) << '\0';
     return Space;
}

//------------------------------------------------------------------------
// Philosopher::Philosopher()
//      constructor
//------------------------------------------------------------------------

Philosopher::Philosopher(char *Name, int Number, int iter)
            : Thread(Name)
{
     No = Number;
     Iteration = iter;
}

//------------------------------------------------------------------------
// Philosopher::ThreadFunc()
//      implement a Philosopher thread
//------------------------------------------------------------------------

void Philosopher::ThreadFunc() 
{
     Thread::ThreadFunc();
     strstream *Space;
     int i;
     
     Space = Filler(No*2);
     for (i = 0; i < Iteration; i++) {
          Delay();
          PhilMonitor.GetChopsticks(No);
          cout << Space->str() << ThreadName.str() << " begins eating." << endl;             
          Delay();
          cout << Space->str() << ThreadName.str() << " finishes eating." << endl;            
          PhilMonitor.PutChopsticks(No);
     }
     Exit();
}

// end of Philospher-Thrd.cpp
