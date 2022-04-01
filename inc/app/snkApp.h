/**
 * @file      snkApp.h
 * @brief     Header file for main game class.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.1
 * @date      01/04/2022
 * @copyright GNU Public License
 */

#ifndef _SNK_APP_H_
#define _SNK_APP_H_

#ifdef __WIN32__
#include "snkWinConsole.h"
#endif /* __WIN32__ */

#ifdef __linux__
#include "snkLinConsole.h"
#endif /* __linux__ */

/**
 * @class  snkApp
 * @brief  Implements draw loop and manages game window.
 */
class snkApp final
{
public:
    snkApp();
    ~snkApp() = default;

    snkApp(const snkApp&  that) = delete;
    snkApp(const snkApp&& that) = delete;

    snkApp& operator=(const snkApp&  that) = delete;
    snkApp& operator=(const snkApp&& that) = delete;

    /**
     * @brief  Starts game loop.
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int Run();

private:
    std::unique_ptr<snkConsole> mConsole;   //! Pointer to appropriate console window
    bool mIsRunning = true;                 //! Signalizes is game still running
};

#endif /* _SNK_APP_H_ */
