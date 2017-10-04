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
        
        unsigned int GetRuntime() const
        {
              return this->runtime;   
        }



};
