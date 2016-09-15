/**
 *   @file      snkWinConsole.h
 *   @brief     Contains class for console window system for Windows OS
 *   @author    Alexander Orel (desperius@gmail.com)
 *   @version   1.0
 *   @date      12.09.2016
 *   @copyright GNU Public License
 */

#ifndef _SNK_WIN_CONSOLE_H_
#define _SNK_WIN_CONSOLE_H_

#ifdef __WIN32__

#include <windows.h>
#include "snkConsole.h"

class snkWinConsole : public snkConsole
{
public:
   snkWinConsole();
   ~snkWinConsole();

   bool Init() override;
   void Close() override;

private:
   HANDLE mMutex {nullptr};
};

#endif /* __WIN32__ */

#endif /* _SNK_WIN_CONSOLE_H_ */