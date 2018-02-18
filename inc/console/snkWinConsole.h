/**
 * @file      snkWinConsole.h
 * @brief     Contains class for console window for Windows.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      15/02/2018
 * @copyright GNU Public License
 */

#ifndef _SNK_WIN_CONSOLE_H_
#define _SNK_WIN_CONSOLE_H_

#ifdef __WIN32__

#include "snkConsole.h"
#include <windows.h>

/**
 * @class snkWinConsole
 * @brief Implements platform specific creation and destroying of Windows console window.
 */
class snkWinConsole : public snkConsole
{
public:
    snkWinConsole();
    virtual ~snkWinConsole();
    snkWinConsole(const snkWinConsole&  that) = delete;
    snkWinConsole(const snkWinConsole&& that) = delete;
    snkWinConsole& operator=(const snkWinConsole&  that) = delete;
    snkWinConsole& operator=(const snkWinConsole&& that) = delete;

private:
    HANDLE mMutex = {nullptr}; //! Handle of Windows mutex
};

#endif /* __WIN32__ */

#endif /* _SNK_WIN_CONSOLE_H_ */
