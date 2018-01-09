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
    void Move(const snkPoint& food, const std::list<snkPoint>& wall);
    void SetDir(Dir dir);

    int GetSpeed()
    {
        return mSpeed;
    }

    void SetSpeed(int speed)
    {
        mSpeed = speed;
    }

    std::list<snkPoint> GetBody()
    {
        return mBody;
    }

    bool IsGameOver()
    {
        return mGameOver;
    }

    bool GetIsFed()
    {
        return mIsFed;
    }

    void SetIsFed(bool isFed)
    {
        mIsFed = isFed;
    }

    void Reset();

private:
    std::list<snkPoint> mBody;
    int mW = {0};
    int mH = {0};
    chtype mSym = {'@'};
    Dir mDir = {Dir::UP};
    int mSpeed = {500}; /* [500; 50] */
    bool mGameOver = {false};
    bool mIsFed = {false};
};

#endif /* _SNK_SNAKE_H_ */
