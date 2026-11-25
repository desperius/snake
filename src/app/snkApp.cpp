/**
 * @brief Contains implementation for main application class.
 */

#include "snkApp.hpp"

#include <cstdlib>

snkApp::snkApp() : mConsole(snkConsole::Create())
{}

int snkApp::Run()
{
    if (!mConsole->Init())
    {
        return EXIT_FAILURE;
    }

    // Starting game loop
    do
    {
        mConsole->Event();
        mIsRunning = mConsole->Loop();
        mConsole->Render();
    }
    while (mIsRunning);

    mConsole->Close();

    return EXIT_SUCCESS;
}
