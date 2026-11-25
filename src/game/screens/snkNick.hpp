/**
 * @brief Contains class for input nickname screen
 */

#pragma once

#include "snkState.hpp"

/**
 * @brief Implements input nickname screen
 */
class snkNick : public snkState
{
public:
    using snkState::snkState;
    ~snkNick() override = default;

    State Update(const int key) override;

protected:
    void Refresh() override;

private:
    static constexpr int MAX_NICK_SIZE = 10; //! Maximal length of player's nickname
};
