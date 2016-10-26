/**
 *   @file      main.h
 *   @brief     Contains all needed includes
 *   @author    Alexander Orel (desperius@gmail.com)
 *   @version   1.0
 *   @date      05.09.2016
 *   @copyright GNU Public License
 */

#ifndef _SNK_MAIN_H_
#define _SNK_MAIN_H_

#include "snkLog.h"

#ifdef __WIN32__

#include "snkWinConsole.h"

#endif /* __WIN32__ */

#ifdef __linux__

#include "snkLinConsole.h"

#endif /* __linux__ */

#endif // _SNK_MAIN_H_
