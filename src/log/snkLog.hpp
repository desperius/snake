/**
 *   @brief Contains class and macros for debugging output
 */

#pragma once

#include <fstream>
#include <string>

/**
 *   Creates file and prints debug output to it in debug mode. Prints nothing in release mode
 */

#ifdef  DEBUG
#define LOG(x) if (mLog.is_open()) { mLog << x << std::endl; }
#else
#define LOG(x)
#endif /* DEBUG */

/**
 * @brief Implements supporting functionality for log output
 */
class snkLog
{
public:
    snkLog(const snkLog& that) = delete;
    snkLog(snkLog&& that) = delete;

    snkLog& operator=(const snkLog& that) = delete;
    snkLog& operator=(snkLog&& that) = delete;

    /**
     * @brief Gets instance of the class
     * @return Reference to object
     */
    static snkLog& Get();
    
    /**
     * @brief Writes log string into output file
     * @param[in] str Text which should be logged
     */
    void Log(std::string& str);

private:
    snkLog();
    ~snkLog();

private:
    std::ofstream mLog; //! Handle of file for log output
};
