/**
 * @brief Contains class for actual game logic
 */

#pragma once

#include <list>

#include "snkState.hpp"
#include "snkLevel.hpp"
#include "snkSnake.hpp"
#include "snkDatabase.hpp"

/**
 * @brief Implements actual game logic
 */
class snkGame : public snkState
{
public:
    snkGame(const int w, const int h);
    ~snkGame() override = default;

    State Update(const int key) override;

protected:
    void Refresh() override;

private:
    static constexpr int FOOD_MAX = 10; //! Maximal number of food per level

    snkLevel mLevel;   //! Represents level state
    snkSnake mSnake;   //! Snake body
    snkPoint mFood;    //! Food on game field
    snkDatabase mRecs; //! Database to write a current score

    std::list<snkPoint> mWall; //! Wall on game field

    int mScore = 0;            //! Current score
    int mFoodNum  = FOOD_MAX;  //! Number of food per current level
    bool mIsStart = true;      //! Indicates level beginning
};
