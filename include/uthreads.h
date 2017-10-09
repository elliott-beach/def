#pragma once

#include <iostream>
#include <setjmp.h>
#include <signal.h>
#include <vector>
#include <map>
#include <deque>
#include <sys/time.h>
#include <algorithm>

/* Forwards */

class Uthreads;
class Thread;

/* Stack size to be used by each thread. Size is in bytes */

#define STACKSIZE 4096 

/* Max Threads */

#define MAXTHREADS 100

#include "logger.h"
#include "scheduler.h"
#include "thread.h"

extern Uthreads* Instance;

class Uthreads
{
   private:
           
          std::map<int, Thread*> ThreadMap;

          /* timer struct val */
           
          struct itimerval time_struct;
          
          int SigCounter;
          
          /* Tests final flag */
          
          bool FinalFlag;
          
          /* Lock flag. Set to true when a test is taking place. */
          
          bool Locked;

   public:
   
          Uthreads();
          
          ~Uthreads();
          
          Logger* Logs = NULL;
          
          void RunTest();
          
          void Initialize();

          void SpawnScheduler();

          void SignalHandler(int Signal);

          void SchedulerConfigure();
          
          void SchedulerSwitch();
          
          std::map<int, Thread*> GetThreads()
          {
                return this->ThreadMap;
          }
      
          bool GetFlag()
          {
              return this->Locked;
          }
          
          int uthread_get_tid();
          
          /* 
           * Returns number of quantums with provided id
           * will be running. "0" will be returned if no thread is found.
           * Otherwise, this function will return number of quantums until
           * it wakes up
           */
 
           int CalculaeUntilQuantum(int TID);


};
