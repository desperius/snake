/**
 * @file      snkWinConsole.cpp
 * @brief     Contains implementation of class for platform specific console window for Windows
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      15/02/2018
 * @copyright GNU Public License
 */

#ifdef __WIN32__

#include "snkWinConsole.h"

snkWinConsole::snkWinConsole()
{
    /* Try to open the mutex */
    mMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, appName.c_str());

    if (!mMutex)
    {
        /* The mutex does not exist. This is the first instance so create the mutex */
        mMutex = CreateMutex(NULL, FALSE, appName.c_str());
    }
    else
    {
        /* Bring existing window to the front */
        SetForegroundWindow(FindWindow(0, appName.c_str()));

        /* The mutex exist so instance should not be created */
        mIsContinue = false;
    }

    SetConsoleTitle(appName.c_str());
}
snkWinConsole::~snkWinConsole()
{
    /* Close Windows mutex */
    ReleaseMutex(mMutex);
}

#endif /* __WIN32__ */
