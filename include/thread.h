#pragma once

class Thread
{
    private:
    
        /* Stack's storage */
        
        char *stack;
        
        int SleepCounter;
        
        unsigned int runtime;

        /* Thread's environment buffer */
        
        sigjmp_buf env;
        
    public:
    
        Thread();
        
        /* Default destructor */
        
        ~Thread();
        
        Thread(void (*args)());
       
        /* How many times has this thread ran? */
        
        unsigned int GetRuntime() const
        {
              return this->runtime;   
        }

        void IncrementRun();

        void SetSleepCounter(int sleeptime);

        int GetSleepCounter() const;
        
        void DecrementSleepCounter();

        /* Returns a reference to the thread's sigjmp_buf buffer */
        
        operator sigjmp_buf&();
        
        
};