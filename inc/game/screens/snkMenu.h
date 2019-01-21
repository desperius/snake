/**
 * @file      snkMenu.h
 * @brief     Contains class for main menu.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      16/02/2018
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
    snkMenu() = default;
    virtual ~snkMenu() = default;

    /**
     * @brief Initializes resources for current game state.
     * @param[in] w Width of game field.
     * @param[in] h Height of game field.
     */
    void Init(int w, int h) override;

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
    State mActive = {State::GAME}; //! Active menu item at the current time
};

#endif /* _SNK_MENU_H_ */
