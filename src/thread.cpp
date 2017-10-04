#include "uthreads.h"
#include "thread.h"

Thread::Thread() 
{
      sigsetjmp(env, 1);
      runtime = 1;
}

Thread::~Thread()
{
      delete stack;
      stack = NULL;
}
void Thread::IncrementRun()
{
      this->runtime++;
}

Thread::operator GetBuffer&()
{
        return this->env;
}
