#ifndef _SNK_LEVEL_H_
#define _SNK_LEVEL_H_

/* + food */
/* # wall */

#include <list>
#include "snkState.h"

class snkLevel
{
public:
    snkLevel() = default;
    ~snkLevel() = default;

    void Init(int w, int h, chtype food_sym, chtype wall_sym);
    std::list<snkPoint> GenWall();
    snkPoint GenFood(const std::list<snkPoint>& body, const std::list<snkPoint>& wall);
    void Move(std::list<snkPoint>& wall, std::chrono::milliseconds currTime);
    int GetLevel();
    void LevelUp();
    void SubLeveUp();
    bool IsWin();

private:
    void hLine(std::list<snkPoint>& wall);
    void vLine(std::list<snkPoint>& wall);
    void hDash(std::list<snkPoint>& wall);
    void vDash(std::list<snkPoint>& wall);

    void hmLine(std::list<snkPoint>& wall);
    void vmLine(std::list<snkPoint>& wall);

    void MoveH();
    void MoveV();

private:
    static const int WALL_SPEED = 800;
    std::chrono::milliseconds mPrevTime;
    std::list<snkPoint> mWallMoveH;
    std::list<snkPoint> mWallMoveV;
    int mW = {0};
    int mH = {0};
    int mFoodCount;
    int mLevelNum = {0};
    int mSubLevel = {0};
    chtype mFoodSym;
    chtype mWallSym;
    bool mIsMoveLeft = {false};
    bool mIsMoveDown = {false};
    bool mIsWin = {false};
    bool mIsStart = {true};
};

#endif /* _SNK_LEVEL_H_ */
