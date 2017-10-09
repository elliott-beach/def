#include "uthreads.h"

Logger::Logger()
{
       logfile.open ("debug.log", std::ios::app);
}

void Logger::Log(const std::string &logline)
{
       std::cout << logline << std::endl;
       logfile << logline << "\n";
}

void Logger::Close()
{
     logfile.close();
}
