#include "snkApp.h"
#include "snkLog.h"

snkApp::snkApp()
{

#ifdef __WIN32__
    mConsole = std::unique_ptr<snkConsole>(new snkWinConsole());
#elif  __linux__
    mConsole = std::unique_ptr<snkConsole>(new snkLinConsole());
#endif

    /* If we didn't create a console window at all */
    if (nullptr == mConsole)
    {
        throw;
    }
}

bool snkApp::Init()
{
    if (false == mConsole->Init())
    {
        return false;
    }

    return true;
}

int snkApp::Run()
{
    if (false == Init())
    {
        return -1;
    }

    while (mRunning)
    {
        Event();
        Loop();
        Render();
    }

    Close();

    return 0;
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
