#include "uthreads.h"
#include "thread.h"
#include "scheduler.h"

int Scheduler::AddThread()
{
       int res = GetMinimunTid();
      
       if (res != -1)
       {
             this->ReadyList.push_back(res);
       }
       
       return res;
}
