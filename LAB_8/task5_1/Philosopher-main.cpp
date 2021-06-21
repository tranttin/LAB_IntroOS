//------------------------------------------------------------------------
// Filename: 
//     Philosopher-main.cpp
// PROGRAM DISCRIPTION
//     This program uses Hoare Style monitor to solve the philospher
//     problem.
//------------------------------------------------------------------------

#include <iostream>
#include <stdlib.h>
#include "ThreadClass.h"
#include "Philosopher-Thrd.h"

//------------------------------------------------------------------------
// main() function
//------------------------------------------------------------------------
int main(int argc, char *argv[]) 
{
     Philosopher *Philosophers[PHILOSOPHERNUM];
     int Iteration;    // The iteration that philosopher implements
     int i;
     strstream name;

     if (argc != 2) {
          cout<<"Use " << argv[0] << " #-of-iterations " << endl;
          exit(0);          
     }      
     else
          Iteration = abs(atoi(argv[1]));

     for (i = 0; i < PHILOSOPHERNUM; i++) { 
          // initialize philosopher threads and run them
          name.seekp(0, ios::beg);
          name << "Philosopher" << i << '\0';
          Philosophers[i] = new Philosopher(name.str(), i, Iteration);
          Philosophers[i]->Begin();
     }
     for (i = 0; i < PHILOSOPHERNUM; i++) {  
          // wait for philosopher threads to terminate
          Philosophers[i]->Join();
     }
     Exit();

 	 return 0;
}
