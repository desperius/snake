/**
 * @file      snkGame.h
 * @brief     Contains class for actual game logic.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.1
 * @date      01/04/2022
 * @copyright GNU Public License
 */

#ifndef _SNK_GAME_H_
#define _SNK_GAME_H_

#include <chrono>

#include "snkState.h"
#include "snkSnake.h"
#include "snkLevel.h"
#include "snkDatabase.h"

/**
 * @class snkGame
 * @brief Implements actual game logic.
 */
class snkGame : public snkState
{
public:
    snkGame(int w, int h);
    virtual ~snkGame() = default;

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
    static const int FOOD_MAX = 10; //! Maximal number of food per level.
    snkSnake mSnake;                //! Snake body
    snkLevel mLevel;                //! Represents level state
    snkPoint mFood;                 //! Food on game field
    snkDatabase mRecs;              //! Database to write a current score
    std::list<snkPoint> mWall;      //! Wall on game field
    int mScore = {0};               //! Current score
    int mFoodNum  = {FOOD_MAX};     //! Number of food per current level
    bool mIsStart = {true};         //! Indicates level beginning
};

#endif /* _SNK_GAME_H_ */
