/**
 * @file      snkNick.h
 * @brief     Contains class for input nickname screen.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.1
 * @date      01/04/2022
 * @copyright GNU Public License
 */

#ifndef _SNK_NICK_H_
#define _SNK_NICK_H_

#include "snkState.h"

/**
 * @class snkNick
 * @brief Implements input nickname screen.
 */
class snkNick : public snkState
{
public:
    using snkState::snkState;
    virtual ~snkNick() = default;

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
    static const int MAX_NICK_SIZE = 10; //! Maximal length of player's nickname
};

#endif /* _SNK_NICK_H_ */
