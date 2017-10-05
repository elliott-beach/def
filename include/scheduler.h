/* Class Scheduler handles threads scheduling */

class Scheduler
{

   private:
        
        /* Blocked list */

        std::vector<int> BlockedList;
   
        std::deque<int> ReadyList;

   public:
   
        int AddThread();


};
