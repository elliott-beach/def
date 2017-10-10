#include "uthreads.h"
#include "thread.h"
#include "arch.h"

Thread::Thread() 
{
        sigsetjmp(env, 1);
        runtime = 1;
}

Thread::Thread(void (*args)())
{
        /* Initialize runtime */
        
        runtime = 0;

        /* Initialize stack and sp */
        
        stack = new char[STACKSIZE];

        /* Initializes env buffer **/
        
        sigsetjmp(env, 1);

        (env->__jmpbuf)[JB_SP] = translate_address((address_t)stack + STACKSIZE-sizeof(address_t));
        (env->__jmpbuf)[JB_PC] = translate_address((address_t)args);
}


void Thread::IncrementRun()
{
      this->runtime++;
}

Thread::~Thread()
{
      delete stack;
      stack = NULL;
}


Thread::operator sigjmp_buf&()
{
        return this->env;
}

void Thread::SetSleepCounter(int sleeptime)
{
        
        /* Sleep counter must be a positive int */
        
        if (sleeptime < 0)
        {
                return;
        }

        Thread::SleepCounter = sleeptime;
}

int Thread::GetSleepCounter() const
{
        return SleepCounter;
}


void Thread::DecrementSleepCounter()
{
        if (this->SleepCounter <= 0)
        {
                this->SleepCounter = 0;
                return;
        }

        this->SleepCounter--;
                
}
