/**
 * @file      snkConsole.h
 * @brief     Contains base class for console window.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.1
 * @date      01/04/2022
 * @copyright GNU Public License
 */

#ifndef _SNK_CONSOLE_H_
#define _SNK_CONSOLE_H_

#include <memory>

#include "snkState.h"

/**
 * @class  snkConsole
 * @brief  Implements base cross-platform functionallity of console window.
 */
class snkConsole
{
public:
    snkConsole() = default;
    virtual ~snkConsole() = 0;

    snkConsole(const snkConsole&  that) = delete;
    snkConsole(const snkConsole&& that) = delete;

    snkConsole& operator= (const snkConsole&  that) = delete;
    snkConsole& operator= (const snkConsole&& that) = delete;

    /**
     * @brief  Initializes needed resources.
     * @return True if an operation is success.
     */
    bool Init();

    /**
     * @brief Handles input events.
     */
    void Event();

    /**
     * @brief  Handles all game's data updates.
     * @return False if game is finished.
     */
    bool Loop();

    /**
     * @brief Handles the rendering processes.
     */
    void Render();

    /**
     * @brief Clean ups and releases resources.
     */
    void Close();

protected:
    /**
     * @brief Create specific curses window.
     * @param[in] h Height in lines of curses window.
     * @param[in] w Width in columns of curses window.
     * @param[in] y Start Y-position in system console window.
     * @param[in] x Start X-position in system console window.
     * @return Pointer to curses window.
     */
    WINDOW* CreateWin(int h, int w, int y, int x);

    /**
     * @brief Delete curses window.
     * @param[in] wnd Pointer to curses window which should be deleted.
     */
    void DeleteWin(WINDOW* wnd);

protected:
    static const std::string appName;     //! Application name
    static const int WIN_W;               //! Window width
    static const int WIN_H;               //! Window height
    static const int SCR_W;               //! Actual game screen width without a border
    static const int SCR_H;               //! Actual game screen height without a border
    State mState = State::MENU;           //! Current game state

    WINDOW* mWin = nullptr;               //! Pointer to curses window which will be main game screen
    WINDOW* mBar = nullptr;               //! Pointer to curses window which will be information panel
    int mKey = 0;                         //! Code of a last pressed key

    //! Pointers to implementation of all possible game states
    std::vector<std::unique_ptr<snkState>> mGameStates;

    snkState* mGameState = nullptr;       //! Pointer to current game state
    bool mIsContinue = true;              //! Indicates is other instance of application was launched
};

#endif /* _SNK_CONSOLE_H_ */
