#include "uthreads.h"

/* Creates an instance so we can log anything from any file */

Uthreads* Instance = NULL;

std::map<int, Thread*> ThreadMap;

static SchedulerManager Scheduler(&ThreadMap);

Uthreads::Uthreads() : FinalFlag(true), Locked(false)
{
        Instance = this;
        this->Logs = new Logger();
        
        std::cout << "Starting uthreads. Settings: Max threads: " <<  MAXTHREADS << " Stack size: " << STACKSIZE << std::endl;       
        std::cout << std::endl;
}

Uthreads::~Uthreads()
{
        this->Logs->Log("Exiting and cleaning maps.. ");
        ThreadMap.clear();
        this->Logs->Close();
}

void Uthreads::Initialize()
{
      /* Testing scheduler */
      
      this->Logs->Log("Testing scheduler");
      SchedulerConfigure();
      SpawnScheduler();
      SchedulerSwitch();
}

void Uthreads::SignalHandler(int Signal)
{	
        SigCounter++;
}


int Uthreads::GetCurrent()
{
        return Scheduler.GetRunningTid();
}


void Uthreads::RunTest()
{
        
        this->Logs->Log("Init thread 0 in map");
        ThreadMap[0] = new Thread();
        
}

int Uthreads::CalculaeUntilQuantum(int TID)
{
        if (!Scheduler.HasThread(TID))
        {
                std::cout << "Thread : " << TID << " not found." << std::endl;
                return 0;
        }

        int SleepTime = Scheduler.TimeUntilWakeup(TID);
        
        if (SleepTime < 0)
        {
                std::cout << "Unable to retrieve wake up time for this tid." << std::endl;
        }
        
        return SleepTime;
}

void Uthreads::SpawnScheduler()
{
        /* Adds a new threads and initializes ThreadMap with first thread */

        Scheduler.AddThread();
        ThreadMap[1] = new Thread();
        this->Logs->Log("Thread #1 added");
        
        try
        {
             if (Scheduler.HasThread(1) && ThreadMap.find(1) != ThreadMap.end()) 
             {
                    std::cout << "OK" << std::endl;
             }
             else
             {
                    std::cout << "Failed" << std::endl;
                    FinalFlag = false;
             }
        }
        catch (...) 
        {
                std::cout << "Failed" << std::endl;
                FinalFlag = false;
        }
}

void Uthreads::SchedulerConfigure()
{
        Scheduler = SchedulerManager(&ThreadMap);
        std::cout << "Initializing thread #0 in Map" << std::endl;
        ThreadMap[0] = new Thread();
        std::cout << "Done!" << std::endl;

        try
        {
                if (Scheduler.GetRunningTid() == 0 && Scheduler.SchedulerRunningTime() == 1 && ThreadMap.find(0) != ThreadMap.end()) 
                {
                        std::cout << "OK" << std::endl;
                } 
                else
                {
                        std::cout << "Failed" << std::endl;
                        FinalFlag = false;
                }
        }
        catch (...) 
        {
                std::cout << "Failed" << std::endl;
                FinalFlag = false;
        }

}

void Uthreads::SchedulerSwitch()
{
        /* Initialize data */
        
        bool TestFlag = true;

        std::cout << "Alternating scheduler" << std::endl;
        
        /* Runs round robin */
        
        std::cout << "Running round robin on 2 thread. Thread #1 will now run. " << std::endl;
        Scheduler.Loop();
        TestFlag &= (Scheduler.GetRunningTid() == 1);

        /* Runs round robin again */
        
        std::cout << "Running round robin on 2 thread. Thread #2 will now run. " << std::endl;
        Scheduler.Loop();
        TestFlag &= (Scheduler.GetRunningTid() == 0);
        
        std::cout << "Adding thread #2" << std::endl;
        Scheduler.AddThread();
        TestFlag &= (Scheduler.HasThread(2) && Scheduler.GetRunningTid() == 0);
        
        std::cout << "Starting thread #2" << std::endl;
        
        ThreadMap[2] = new Thread();
        std::cout << "Done" << std::endl;
        TestFlag &= (ThreadMap.find(2) != ThreadMap.end());
        
        Scheduler.Loop();
        std::cout << "Running round robin on #3" << std::endl;
        TestFlag &= (Scheduler.GetRunningTid() == 1);
      
}

int main()
{
        new Uthreads();
        Instance->Initialize();
        delete Instance;
        return 0;
}
