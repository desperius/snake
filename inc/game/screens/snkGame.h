#ifndef _SNK_GAME_H_
#define _SNK_GAME_H_

#include <chrono>

#include "snkState.h"
#include "snkSnake.h"
#include "snkLevel.h"
#include "snkDatabase.h"

class snkGame : public snkState
{
public:
    snkGame() = default;
    virtual ~snkGame() = default;

    void Init(int w, int h) override;
    State Update(int key) override;

private:
    void Refresh() override;

private:
    static const int FOOD_MAX = 10;
    snkSnake mSnake;
    snkPoint mFood;
    snkDatabase mRecs;
    std::list<snkPoint> mWall;
    snkLevel mLevel;
    int mScore = {0};
    int mFoodNum  = {FOOD_MAX};
    bool mIsStart = {true};
};

#endif /* _SNK_GAME_H_ */
