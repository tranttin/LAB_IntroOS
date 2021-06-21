//------------------------------------------------------------------------
// Filename: 
//     Philosopher-mon.cpp
// PROGRAM DISCRIPTION
//     PhilosopherMonitor class implementation file
//------------------------------------------------------------------------

#include <iostream.h>
#include <stdlib.h>
#include "ThreadClass.h"
#include "Philosopher-Thrd.h"
#include "Philosopher-mon.h"

//------------------------------------------------------------------------
// PhilosopherMonitor::PhilosopherMonitor()
//      constructor 
//------------------------------------------------------------------------

PhilosopherMonitor::PhilosopherMonitor(char* Name)
                    : Monitor(Name, HOARE) 
{
     for (int i = 0; i < PHILOSOPHERNUM; i++) {
          state[i] = THINKING;    // initially, all philosophers are thinking
          strstream *ConditionName;
          ConditionName = new strstream;
          ConditionName->seekp(0, ios::beg);
          (*ConditionName) << "Self" << i << '\0';
          self[i] = new Condition(ConditionName->str());         
     }
}

//------------------------------------------------------------------------
// PhilosopherMonitor::Test(int Number)
//   Check if philosopher Number can have two chopsticks and eat
//   int Number     --   The number of the philosopher
//------------------------------------------------------------------------

void PhilosopherMonitor::Test(int Number)
{
     if (state[(Number+PHILOSOPHERNUM-1)%PHILOSOPHERNUM] != EATING &&  // left is not eating
         state[Number] == HUNGRY                                   &&  // I am hungry, and
         state[(Number+1)%PHILOSOPHERNUM] != EATING ) {                // right is not eating 
          state[Number] = EATING;       // philosopher Number can eat
          self[Number]->Signal();       // wake him up
     }
}

//------------------------------------------------------------------------
// FUNCTION  GetChopsticks(int):
//   This function implement a philosopher picking up two chopsticks
//   int Number     --   The number of the philosopher
//------------------------------------------------------------------------

void PhilosopherMonitor::GetChopsticks(int Number)
{
     MonitorBegin();
     state[Number] = HUNGRY;       // I am hungry
     Test(Number);                 // Test if I can eat
     if (state[Number] != EATING)  // if the test result says no, 
          self[Number]->Wait();    // then wait
     MonitorEnd();                 // finally, I can eat
}

//------------------------------------------------------------------------
// FUNCTION  PutChopsticks(int):
//   This function implement a philosopher returning two chopsticks
//   int Number     --   The number of the philosopher
//------------------------------------------------------------------------

void  PhilosopherMonitor::PutChopsticks(int Number)
{
     MonitorBegin();
     state[Number] = THINKING;          // go back to thinking
     Test((Number+PHILOSOPHERNUM-1) % PHILOSOPHERNUM); // let my left neighbor eat
     Test((Number+1)%PHILOSOPHERNUM);   // let my right neighbor eat
     MonitorEnd();
}

// end of Philospher-mon.cpp
