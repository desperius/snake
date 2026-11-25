/**
 * @brief Header file for main application class
 */

#pragma once

#include "snkConsole.hpp"

#ifdef __WIN32__
// #include "snkWinConsole.h"
#endif /* __WIN32__ */

#ifdef __linux__
// #include "snkLinConsole.h"
#endif /* __linux__ */

/**
 * @brief Implements draw loop and manages game window
 */
class snkApp final
{
public:
    snkApp();
    ~snkApp() = default;

    snkApp(const snkApp& that) = delete;
    snkApp(snkApp&& that) = delete;

    snkApp& operator=(const snkApp& that) = delete;
    snkApp& operator=(snkApp&& that) = delete;

    /**
     * @brief  Starts game loop
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int Run();

private:
    std::unique_ptr<snkConsole> mConsole;   //!< Pointer to appropriate console window
    bool mIsRunning = false;                //!< Signalizes is game still running
};
