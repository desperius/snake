/**
 * @file      snkApp.cpp
 * @brief     Contains implementation for main game class.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.1
 * @date      01/04/2022
 * @copyright GNU Public License
 */

#include "snkApp.h"

snkApp::snkApp()
{

#ifdef __WIN32__
    mConsole = std::make_unique<snkWinConsole>();
#elif  __linux__
    mConsole = std::make_unique<snkLinConsole>();
#endif

    /* We didn't create a console window at all */
    if (!mConsole)
    {
        throw;
    }
}

int snkApp::Run()
{
    if (!mConsole->Init())
    {
        return EXIT_FAILURE;
    }

    /* Starting game loop */
    while (mIsRunning)
    {
        mConsole->Event();
        mIsRunning = mConsole->Loop();
        mConsole->Render();
    }

    mConsole->Close();

    return EXIT_SUCCESS;
}
