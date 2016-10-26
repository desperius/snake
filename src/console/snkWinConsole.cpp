/**
 *   @file      snkWinConsole.cpp
 *   @brief     Contains implementation of class for console window system for Windows OS
 *   @author    Alexander Orel (desperius@gmail.com)
 *   @version   1.0
 *   @date      12.09.2016
 *   @copyright GNU Public License
 */

#ifdef __WIN32__

#include "snkWinConsole.h"

snkWinConsole::snkWinConsole()
{
}

snkWinConsole::~snkWinConsole()
{
}

bool snkWinConsole::Init()
{
   // Try to open the mutex
   mMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, appName.c_str());

   if (!mMutex)
   {
      // The mutex does not exist. This is the first instance so create the mutex
      mMutex = CreateMutex(NULL, FALSE, appName.c_str());
   }
   else
   {
      // Bring existing window to the front
      SetForegroundWindow(FindWindow(0, appName.c_str()));

      // The mutex exist so return
      return false;
   }

   SetConsoleTitle(appName.c_str());

   return true;
}

void snkWinConsole::Close()
{
   ReleaseMutex(mMutex);
}

#endif /* __WIN32__ */
