/**
 *   @file      snkLog.h
 *   @brief     Contains implementation of class and macros for debugging output
 *   @author    Alexander Orel (desperius@gmail.com)
 *   @version   1.0
 *   @date      17/02/2018
 *   @copyright GNU Public License
 */

#include "snkLog.h"

snkLog& snkLog::Get()
{
    static snkLog log;
    return log;
}

void snkLog::Log(std::string& str)
{
    LOG(str);
}

snkLog::snkLog()
{
    mLog.open("log", std::ios::trunc);
}

snkLog::~snkLog()
{
    mLog.close();
}
