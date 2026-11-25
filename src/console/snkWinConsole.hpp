/**
 * @brief Contains class for console window for Windows
 */

#pragma once

#ifdef _WIN32

#include "snkConsole.hpp"
#include <windows.h>

/**
 * @brief Implements platform specific creation and destroying of Windows console window
 */
class snkWinConsole : public snkConsole
{
public:
    snkWinConsole();
    ~snkWinConsole() override;
    snkWinConsole(const snkWinConsole& that) = delete;
    snkWinConsole(snkWinConsole&& that) = delete;
    snkWinConsole& operator=(const snkWinConsole& that) = delete;
    snkWinConsole& operator=(snkWinConsole&& that) = delete;

protected:
    bool InitScr() override;

private:
    HANDLE mMutex = nullptr; //! Handle of Windows mutex
};

#endif /* _WIN32 */
