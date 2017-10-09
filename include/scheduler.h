#pragma once

/* Class Scheduler handles threads scheduling */

class SchedulerManager
{

   private:

        std::deque<int> ReadyList;
        
        /* Waiting list: sleeping threads */
        
        std::vector<int> AwaitingList;

        /* Blocked list */
        
        std::vector<int> BlockedList;
        
        bool VacancyList[MAXTHREADS] = {0};

        std::map<int, Thread*> *SchedulerMap;
        
        /* Handles int that tells which thread is running */
        
        int Running;
        
        /* Number of round robin iterations */
        
        int RunTimes;

        /* Records backtrace buffer. For instance, when a thread is put to sleep, or is blocked */
        
        int Backtrace;
        
   public:
   
        int ResumeThread(int tid);
       
        /* Constructor */
        
        SchedulerManager(std::map<int, Thread*> *db);
       
       /* 
        * Kills a thread. Forces and removes a thread, specially by:
        *
        * i) Removing it from vacancy list
        * 
        * iii) Vacating thread id.
        * 
        * This function returns 0 if thread was 'killed', and -1 if it wasn't.
        */
       
        int Kill(int tid);

        int TimeUntilWakeup(int tid);
      
        int SleepThread(int Quantums);

        /* Counts ReadyList vector */

        unsigned int CountReady() const
        {
               return this->ReadyList.size();
        }
        
        int SchedulerRunningTime();

        /* Returns current thread ID */
        
        int GetRunningTid();

        int GetLastAvailableTid();
                  
        /* Adds a new thread */
        
        int AddThread();

        /* Checks if a thread exists */
        
        bool HasThread(int tid);
        
        /* Updates threads */
        
        int Loop();
};
