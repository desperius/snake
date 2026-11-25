/**
 * @brief     Contains class for main menu
 */

#pragma once

#include "snkState.hpp"

/**
 * @brief Implements main menu
 */
class snkMenu : public snkState
{
public:
    using snkState::snkState;
    ~snkMenu() override = default;

    State Update(const int key) override;

protected:
    void Refresh() override;

private:
    static constexpr int8_t MAJOR = 1; //! Major part of game version
    static constexpr int8_t MINOR = 1; //! Minor part of game version
    State mActive = State::GAME;       //! Active menu item at the current time
};
