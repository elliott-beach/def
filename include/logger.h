#pragma once

#include <fstream>

struct Logger
{
    std::ofstream logfile;
    
    /* Constructor, opens logfile */

    Logger();
    
    /* Appends a line */

    void Log(const std::string &logline);

    /* Closes ofstream pointer */
    
    void Close();
};
