#include "uthreads.h"
#include "thread.h"

Thread::Thread() 
{
      sigsetjmp(env, 1);
      runtime = 1;
}

