/**
 * @file      snkApp.cpp
 * @brief     Contains implementation for main game class.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      14.02.2018
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
    if (false == Init())
    {
        return EXIT_FAILURE;
    }

    while (mRunning)
    {
        Event();
        Loop();
        Render();
    }

    Close();

    return EXIT_SUCCESS;
}

bool snkApp::Init()
{
    return mConsole->Init();
}

void snkApp::Event()
{
    mConsole->Event();
}

void snkApp::Loop()
{
    mRunning = mConsole->Loop();
}

void snkApp::Render()
{
    mConsole->Render();
}

void snkApp::Close()
{
    mConsole->Close();
}
