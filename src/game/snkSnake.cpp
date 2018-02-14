/**
 * @file      snkState.cpp
 * @brief     Contains implementation of class for snake management.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      15/02/2018
 * @copyright GNU Public License
 */

#include "snkSnake.h"
#include <algorithm>

using namespace std::chrono;

void snkSnake::Init(int w, int h, chtype sym)
{
    mW = w;
    mH = h;
    mSym = sym;

    mPrevTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    Reset();
}

void snkSnake::Move(const snkPoint& food, const std::list<snkPoint>& wall, milliseconds currTime)
{
    if (mGameOver)
    {
        return;
    }

    milliseconds delta = currTime - mPrevTime;

    if (delta.count() < mSpeed)
    {
        return;
    }

    mPrevTime = currTime;

    int x = mBody.front().mX;
    int y = mBody.front().mY;
    snkPoint head(x, y, mSym, BLU_BLACK);

    switch (mDir)
    {
        case Dir::UP:
        {
            head.mY -= 1;
            break;
        }

        case Dir::DN:
        {
            head.mY += 1;
            break;
        }

        case Dir::RT:
        {
            head.mX += 1;
            break;
        }

        case Dir::LF:
        {
            head.mX -= 1;
            break;
        }

        default:
        {
            break;
        }
    }

    /* Reached right or left border */
    if (head.mX >= mW || head.mX < 0)
    {
        mGameOver = true;
        return;
    }

    /* Reached bottom or top border */
    if (head.mY >= mH || head.mY < 0)
    {
        mGameOver = true;
        return;
    }

    /* Moving wall hit the snake's body */
    for (auto& brick : wall)
    {
        auto comparator = [&brick] (const snkPoint & point)
        {
            return (point.mX == brick.mX) && (point.mY == brick.mY);
        };

        auto hit = std::find_if(mBody.begin(), mBody.end(), comparator);

        if (hit != mBody.end())
        {
            mGameOver = true;
            return;
        }
    }

    auto comparator = [&head] (const snkPoint & point)
    {
        return (point.mX == head.mX) && (point.mY == head.mY);
    };

    auto biteBody = std::find_if(mBody.begin(), mBody.end(), comparator);
    auto biteWall = std::find_if(wall.begin(), wall.end(), comparator);

    /* Snake bites itself or bites a wall */
    if ((biteBody != mBody.end()) || (biteWall != wall.end()))
    {
        mGameOver = true;
        return;
    }

    /* Snake bites the food */
    if (comparator(food))
    {
        mBody.front().mCol = mBody.back().mCol;
        mBody.push_front(head);
        mIsFed = true;
    }
    else
    {
        mBody.front().mCol = mBody.back().mCol;
        mBody.pop_back();
        mBody.push_front(head);
        mIsFed = false;
    }
}

void snkSnake::SetDir(Dir dir)
{
    Dir prev_dir = mDir;
    mDir = dir;

    /* If press same direction key, snake will move in reverse direction and bite itself in same exact moment */
    if (prev_dir != mDir)
    {
        short is_reversed = static_cast<short>(prev_dir) + static_cast<short>(mDir);

        /* If snake at the moment moves exactly opposite direction to previous one */
        if (is_reversed % 2 == 0)
        {
            mBody.front().mCol = mBody.back().mCol;
            mBody.reverse();
        }
    }
}

int snkSnake::GetSpeed()
{
    return mSpeed;
}

void snkSnake::SetSpeed(int speed)
{
    mSpeed = speed;
}

std::list<snkPoint> snkSnake::GetBody()
{
    return mBody;
}

bool snkSnake::IsGameOver()
{
    return mGameOver;
}

bool snkSnake::GetIsFed()
{
    return mIsFed;
}

void snkSnake::SetIsFed(bool isFed)
{
    mIsFed = isFed;
}

void snkSnake::Reset()
{
    int cx = mW / 2 + 6;
    int cy = mH / 2 + 6;

    mBody.clear();
    mBody.push_back(snkPoint(cx, cy + 0, mSym, BLU_BLACK));
    mBody.push_back(snkPoint(cx, cy + 1, mSym));
    mBody.push_back(snkPoint(cx, cy + 2, mSym));

    mDir = {Dir::UP};
    mGameOver = false;
    mIsFed = false;
}

void snkSnake::ResetSpeed()
{
    mSpeed = INIT_SPEED;
}
