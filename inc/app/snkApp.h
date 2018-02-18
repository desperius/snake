/**
 * @file      snkApp.h
 * @brief     Header file for main game class.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      14/02/2018
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
class snkApp
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
    int  Run();

private:
    /**
     * @brief  Initializes needed resources.
     * @return True if an operation is succeess.
     */
    bool Init();

    /**
     * @brief Handles input events.
     */
    void Event();

    /**
     * @brief Handles all game's data updates.
     */
    void Loop();

    /**
     * @brief Handles the rendering processes.
     */
    void Render();

    /**
     * @brief Clean ups and releases recourses.
     */
    void Close();

private:
    std::unique_ptr<snkConsole> mConsole;   //! Pointer to appropriate console window
    bool mRunning = {true};                 //! Signalizes is game still running
};

#endif /* _SNK_APP_H_ */
