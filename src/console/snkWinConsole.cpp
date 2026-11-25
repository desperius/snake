/**
 * @brief Contains implementation of class for platform specific console window for Windows
 */

#ifdef _WIN32

#include "snkWinConsole.hpp"

snkWinConsole::snkWinConsole()
{
    // Try to create the mutex or open the existed one
    mMutex = CreateMutex(nullptr, FALSE, appName.c_str());

    if (!mMutex)
    {
        // Creation or opening the mutex failed. Show the error message
        const DWORD errorCode = GetLastError();
        CHAR errorDescription[1024] = {};
        constexpr DWORD flags = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
        const DWORD messageLength = FormatMessage(flags, nullptr, errorCode, 0, errorDescription, std::size(errorDescription), nullptr);

        std::string message = "Windows could not create or open the mutex.\n\nWindows error " + std::to_string(errorCode) + ":\n";
        message += messageLength ? errorDescription : "No error description is available.";
        MessageBox(nullptr, message.c_str(), "Startup error", MB_OK | MB_ICONERROR);

        mIsUnique = false;
    }
    else if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        // Bring existing window to the front
        SetForegroundWindow(FindWindow(nullptr, appName.c_str()));

        // The mutex exist so instance should not be created
        mIsUnique = false;
    }

    SetConsoleTitle(appName.c_str());
}
snkWinConsole::~snkWinConsole()
{
    // Close Windows mutex
    CloseHandle(mMutex);
}

bool snkWinConsole::InitScr()
{
    return initscr() != nullptr;
}

#endif /* _WIN32 */
