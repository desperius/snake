#ifndef _SNK_SNAKE_H_
#define _SNK_SNAKE_H_

#include <list>

#include "snkState.h"

enum class Dir : short
{
    UP = 1,
    LF = 2,
    DN = 3,
    RT = 4
};

class snkSnake
{
public:
    snkSnake()  = default;
    ~snkSnake() = default;

    void Init(int w, int h, chtype sym);
    void Move(const snkPoint& food);
    void SetDir(Dir dir);

    int GetSpeed()
    {
        return mSpeed;
    }

    std::list<snkPoint> GetBody()
    {
        return mBody;
    }

    bool IsGameOver()
    {
        return mGameOver;
    }

    bool IsFed()
    {
        return mFed;
    }

    void Reset();

private:
    std::list<snkPoint> mBody;
    int mW = {0};
    int mH = {0};
    chtype mSym = {'@'};
    Dir mDir = {Dir::UP};
    int mSpeed = {500};
    bool mGameOver = {false};
    bool mFed = {false};
};

#endif /* _SNK_SNAKE_H_ */
