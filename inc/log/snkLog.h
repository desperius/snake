/**
 *   @file      snkLog.h
 *   @brief     File contains functions and macros for debugging
 *   @author    Alexander Orel (desperius@gmail.com)
 *   @version   1.0
 *   @date      05.09.2016
 *   @copyright GNU Public License
 */

#ifndef _SNK_LOG_H_
#define _SNK_LOG_H_

#include <iostream>

/**
 *   @def LOG(x)
 *   Prints debug output in debug mode. Prints nothing in release mode.
 */

#ifdef  DEBUG
#define LOG(x) do { std::cout << x << std::endl; } while(0)
#else
#define LOG(x)
#endif /* DEBUG */

#endif /* _SNK_LOG_H_ */
