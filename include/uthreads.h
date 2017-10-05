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
class Scheduler;

extern Uthreads* Instance;

/* Stack size to be used by each thread (size is in bytes) */

#define STACKSIZE 4096 

/* Max Threads */

#define MAXTHREADS 100

#include "arch.h"
#include "scheduler.h"
#include "thread.h"

class Uthreads
{
   private:
           
          std::map<int, Thread*> ThreadMap;
};
