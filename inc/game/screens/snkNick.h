/**
 * @file      snkNick.h
 * @brief     Contains class for input nickname screen.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      16/02/2018
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
    snkNick() = default;
    virtual ~snkNick() = default;

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

    /**
     * @brief Creates border of frame for nickname input field.
     * @param[in] l Symbol for left side of frame.
     * @param[in] m Symbol for middle side of frame.
     * @param[in] r Symbol for right side of frame.
     * @return Final vector of frame.
     */
    std::vector<chtype> GenLine(chtype l, chtype m, chtype r);

private:
    static const int MAX_NICK_SIZE = 10; //! Maximal length of player's nickname
};

#endif /* _SNK_NICK_H_ */
