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
