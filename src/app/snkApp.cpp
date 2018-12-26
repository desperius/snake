/**
 * @file      snkApp.cpp
 * @brief     Contains implementation for main game class.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      26.12.2018
 * @copyright GNU Public License
 */

#include "snkApp.h"

snkApp::snkApp()
{

#ifdef __WIN32__
    mConsole = std::unique_ptr<snkConsole>(new snkWinConsole());
#elif  __linux__
    mConsole = std::unique_ptr<snkConsole>(new snkLinConsole());
#endif

    /* We didn't create a console window at all */
    if (nullptr == mConsole)
    {
        throw;
    }
}

int snkApp::Run()
{
    if (false == mConsole->Init())
    {
        return EXIT_FAILURE;
    }

    /* Starting game loop */
    while (mRunning)
    {
        mConsole->Event();
        mRunning = mConsole->Loop();
        mConsole->Render();
    }

    mConsole->Close();

    return EXIT_SUCCESS;
}
