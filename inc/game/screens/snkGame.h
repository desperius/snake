#ifndef _SNK_GAME_H_
#define _SNK_GAME_H_

#include "snkState.h"
#include "snkSnake.h"
#include "snkLevel.h"
#include <chrono>

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
    std::chrono::milliseconds mTime;
    snkSnake mSnake;
    snkPoint mFood;
    std::list<snkPoint> mWall;
    snkLevel mLevel;
    int mScore = {0};
    int mLevelNum = {1};
    int mFoodNum  = {3};
    bool mIsLvlStart = {true};
};

#endif /* _SNK_GAME_H_ */
