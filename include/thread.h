#pragma once

/* Stack size to be used by each thread. Size is in bytes */

#define STACKSIZE 4096 

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
    
        ~Thread();

        Thread(void (*args)());
    
        /* How many times has this thread ran? */
        
        unsigned int GetRuntimes() const
        {
              return this->runtime;   
        }
    
        void IncrementRun();

        /* Returns a reference to the thread's sigjmp_buf buffer */

        operator GetBuffer&();


};
