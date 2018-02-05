/**
 *   @file      snkLog.h
 *   @brief     File contains class and macros for debugging output
 *   @author    Alexander Orel (desperius@gmail.com)
 *   @version   1.0
 *   @date      20.12.2017
 *   @copyright GNU Public License
 */

#ifndef _SNK_LOG_H_
#define _SNK_LOG_H_

#include <fstream>
#include <string>

/**
 *   @def LOG(x)
 *   Creates file and prints debug output to it in debug mode. Prints nothing in release mode.
 */

#ifdef  DEBUG
#define LOG(x) if (mLog.is_open()) { mLog << x << std::endl; }
#else
#define LOG(x)
#endif /* DEBUG */

class snkLog
{
public:
    snkLog(const snkLog& that) = delete;
    snkLog(const snkLog&& that) = delete;
    snkLog& operator=(const snkLog& that) = delete;
    snkLog& operator=(const snkLog&& that) = delete;

    static snkLog& Get();
    void Log(std::string& str);

private:
    snkLog();
    ~snkLog();

private:
    std::ofstream mLog;
};

#endif /* _SNK_LOG_H_ */
