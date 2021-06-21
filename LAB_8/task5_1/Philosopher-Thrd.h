//------------------------------------------------------------------------
// Filename: 
//     Philosopher-Thrd.h
// PROGRAM DISCRIPTION
//     Interface file for Philosopher thread class
//------------------------------------------------------------------------

#ifndef  _PHILOSOPHER_THRD_H
#define  _PHILOSOPHER_THRD_H

#include "ThreadClass.h"

#define PHILOSOPHERNUM   5
#define AVAILABLE        1
#define NOT_AVAILABLE    0

//------------------------------------------------------------------------
// Philosopher class definition
//------------------------------------------------------------------------

class Philosopher: public Thread 
{
     public:
          Philosopher(char *Name, int Number, int iter);  // constructor

     private:
          int No;     // position of the philosopher
          int Iteration;
          void ThreadFunc();
};

#endif
