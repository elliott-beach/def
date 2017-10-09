#include "uthreads.h"
#include "scheduler.h"
#include "thread.h"

SchedulerManager::SchedulerManager(std::map<int, Thread*> *db) : SchedulerMap(db), Running(0),  RunTimes(0), Backtrace(-1)
{
        VacancyList[0] = true;
}

int SchedulerManager::Loop()
{
        RunTimes++;
        
        for (auto i = AwaitingList.begin(); i != AwaitingList.end(); )
        {	
                  if  (SchedulerMap->find(*i) == SchedulerMap->end())
                  {
                         std::cerr << "Unable to find thread." << std::endl;
                         return -1;
                  }
                  
                  if ((*SchedulerMap)[*i]->GetSleepCounter() == 0)
                  {
                         ReadyList.push_back(*i);
                         i = AwaitingList.erase(i);
                  }
                  else
                  {
                         (*SchedulerMap)[*i]->DecrementSleepCounter();
                         i++;
                  }
        }
         
        /* Sets current running thread in the back of ReadyList */
         
        if (Running != -1)
        {
                /* Puts new thread in the back of ReadyList vector */
                
                ReadyList.push_back(Running);
        }

        /* Pops next thread to running thread */
        
        Running = ReadyList.front();
    
        if (SchedulerMap->find(Running) == SchedulerMap->end())
        {
             std::cerr << "thread library error: couldn't find matching " "thread instance in thread DB" << std::endl;
             return -1;
        }

        /* Increments thread's counter */
    
        (*SchedulerMap)[Running]->IncrementRun();

        /* Deletes running thread from ReadyList */
    
        ReadyList.pop_front();

        Backtrace = -1;

        /* Returns PID of recently created thread */
    
        return Running;
}

int SchedulerManager::GetLastAvailableTid() 
{
       for (unsigned int i = 0; i < MAXTHREADS; ++i) 
       {
               if (!VacancyList[i])
               {
                      /* We use flag '1' to indicate that this TID is taken */
 
                      VacancyList[i] = 1;
                      return i;
               }
       }

       /* No slots available */

       return -1;
}

int SchedulerManager::AddThread()
{
       int res = GetLastAvailableTid();
      
       if (res != -1)
       {
             this->ReadyList.push_back(res);
       }
       
       Instance->Logs->Log("New thread created: " + std::to_string(res));
       
       return res;
}


int SchedulerManager::GetRunningTid() 
{
       if (Running == -1 && Backtrace != -1)
       {
            return Backtrace;
       }

       return Running;
}

int SchedulerManager::ResumeThread(int tid)
{
       if (!HasThread(tid))
       {	
               /* Returns -1 if thread hasn't been found */
              
               return -1;
       }    
         
       if (std::find(BlockedList.begin(), BlockedList.end(), tid) != BlockedList.end())
       {
               /* If tid found, we proceed to remove it from blocked listing*/
                    
               BlockedList.erase(std::find(BlockedList.begin(), BlockedList.end(), tid));

               /* Adds this tid to ReadyList */
                    
               ReadyList.push_back(tid);
       }
         
       return 0;
}

bool SchedulerManager::HasThread(int tid)
{
       return this->VacancyList[tid];
}

int SchedulerManager::Kill(int tid)
{
      if (!HasThread(tid))
      {
           return -1;
      }
      
      /* Looks up into sleeping vector */
      
      if (std::find(AwaitingList.begin(), AwaitingList.end(), tid) != AwaitingList.end())
      {
            /* This thread is meant to run anytime soon. Unable to remove */
           
            return -1;
      }
      
      VacancyList[tid] = false;
      
      /* Sets Running handler to -1, in case that we're killing a running thread */
      
      if (this->Running == tid)
      {
            Running = -1;
      }
      else if (std::find(ReadyList.begin(), ReadyList.end(), tid) != ReadyList.end())
      {
            /* Removes this thread if it's found within ReadyList */
            
            ReadyList.erase(std::find(ReadyList.begin(), ReadyList.end(), tid));
      }
      else if (std::find(BlockedList.begin(), BlockedList.end(), tid) != BlockedList.end())
      {
           /* Removes this thread from BlockdeList */
           
           BlockedList.erase(std::find(BlockedList.begin(), BlockedList.end(), tid));
           
           Instance->Logs->Log("TID removed: " + std::to_string(tid));
      }

      return 0;
}

int SchedulerManager::TimeUntilWakeup(int tid)
{
      std::map<int, Thread*> Maps = Instance->GetThreads();

      if (!HasThread(tid) || Maps.find(tid) == Maps.end())
      {
             return -1;
      }  
      
      /* Checks if thread is not asleep */
      
      if (std::find(AwaitingList.begin(), AwaitingList.end(), tid) == AwaitingList.end())
      {
             return 0;
      }

      return (Maps)[tid]->GetSleepCounter() + 1;
}


int SchedulerManager::SleepThread(int Quantums)
{
      if (Quantums < 1)
      {
          return -1;
      }

      if (!Running)
      {
           return -1;
      }
      
      if (SchedulerMap->find(Running) == SchedulerMap->end())
      { 
            return -1;
      }

      (*SchedulerMap)[Running]->SetSleepCounter(Quantums);

      AwaitingList.push_back(Running);

      Backtrace = Running;

      Running = -1;
      
      return 0;
}

int SchedulerManager::SchedulerRunningTime()
{
     return this->RunTimes + 1;
}
