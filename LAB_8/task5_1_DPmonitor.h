//------------------------------------------------------------------------
// Filename: 
//     Philosopher-mon.h
// PROGRAM DISCRIPTION
//     Interface file for PhilosopherMonitor thread class
//
//    MONITOR  philosopher, Hoare Style:                                               
//    This monitor solves the philosopher problem.  It consists 
//    of the following procedures:                                     
//    (1) Test(int Number)       - test if philosopher Number can eat
//    (2) GetChopSticks(int i)   - philosopher i want chopsticks
//    (3) PutChopSticks(int i)   - philosopher i put chopsticks down
//------------------------------------------------------------------------

#ifndef  _PHILOSOPHER_MON_H
#define  _PHILOSOPHER_MON_H

#include "ThreadClass.h"

// enum define 

enum State { THINKING, HUNGRY, EATING };  // philosopher states

//------------------------------------------------------------------------
// PhilosopherMonitor class definition
//------------------------------------------------------------------------

class PhilosopherMonitor: public Monitor 
{
     public:
          PhilosopherMonitor(char* Name);
          void  GetChopsticks(int PhilospherNumber);      //  pick up the chopstick
          void  PutChopsticks(int PhilospherNumber);      //  put down the chopstick

     private:
          void      Test(int Number);
          Condition *self[PHILOSOPHERNUM];
          State     state[PHILOSOPHERNUM];
};

#endif
