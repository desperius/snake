/**
 * @file      snkMenu.h
 * @brief     Contains class for main menu.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.1
 * @date      01/04/2022
 * @copyright GNU Public License
 */

#ifndef _SNK_MENU_H_
#define _SNK_MENU_H_

#include "snkState.h"

/**
 * @class snkMenu
 * @brief Implements main menu.
 */
class snkMenu : public snkState
{
public:
    using snkState::snkState;
    virtual ~snkMenu() = default;

    /**
     * @brief Updates actual game data based on input.
     * @param[in] key Code of pressed key.
     * @return Current game state.
     */
    State Update(int key) override;

private:
    /**
     * @brief Refresh values of game field and status bar.
     */
    void Refresh() override;

private:
    static const int8_t MAJOR = 1; //! Major part of game version
    static const int8_t MINOR = 0; //! Minor part of game version
    State mActive = State::GAME;   //! Active menu item at the current time
};

#endif /* _SNK_MENU_H_ */
