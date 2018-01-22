#include "snkSnake.h"
#include <algorithm>

void snkSnake::Init(int w, int h, chtype sym)
{
    mW = w;
    mH = h;
    mSym = sym;

    Reset();
}

void snkSnake::Move(const snkPoint& food, const std::list<snkPoint>& wall)
{
    if (mGameOver)
    {
        return;
    }

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
    }

    /* Reached bottom or top border */
    if (head.mY >= mH || head.mY < 0)
    {
        mGameOver = true;
    }

    snkPoint left = wall.front();
    snkPoint right = wall.back();

    auto leftHitComparator = [&left] (const snkPoint & point)
    {
        return (point.mX == left.mX) && (point.mY == left.mY);
    };

    auto rightHitComparator = [&right] (const snkPoint & point)
    {
        return (point.mX == right.mX) && (point.mY == right.mY);
    };

    auto hitBodyL = std::find_if(mBody.begin(), mBody.end(), leftHitComparator);
    auto hitBodyR = std::find_if(mBody.begin(), mBody.end(), rightHitComparator);

    /* Moving wall hit the snake's body */
    if ((hitBodyL != mBody.end()) || (hitBodyR != mBody.end()))
    {
        mGameOver = true;
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
