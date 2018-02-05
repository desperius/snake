#include "snkLevel.h"
#include <algorithm>
#include <cstdlib>

using namespace std::chrono;

void snkLevel::Init(int w, int h, chtype food_sym, chtype wall_sym)
{
    mW = w;
    mH = h;
    mFoodSym = food_sym;
    mWallSym = wall_sym;

    mPrevTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    srand(mPrevTime.count());
}

std::list<snkPoint> snkLevel::GenWall()
{
    std::list<snkPoint> wall;

    switch (mLevelNum)
    {
        case 1:
        {
            hLine(wall);
            break;
        }

        case 2:
        {
            vLine(wall);
            break;
        }

        case 3:
        {
            hLine(wall);
            vLine(wall);
            break;
        }

        case 4:
        {
            hDash(wall);
            break;
        }

        case 5:
        {
            vDash(wall);
            break;
        }

        case 6:
        {
            hDash(wall);
            vDash(wall);
            break;
        }

        case 7:
        {
            hmLine(wall);
            mWallMoveH = wall;
            break;
        }

        case 8:
        {
            vmLine(wall);
            mWallMoveV = wall;
            break;
        }

        case 9:
        {
            mWallMoveH.clear();
            mWallMoveV.clear();

            hmLine(mWallMoveH);
            vmLine(mWallMoveV);

            wall = mWallMoveH;
            wall.insert(wall.end(), mWallMoveV.begin(), mWallMoveV.end());
        }

        default:
        {
            break;
        }
    }

    mIsMoveLeft = false;
    mIsMoveDown = false;

    return wall;
}

snkPoint snkLevel::GenFood(const std::list<snkPoint>& body, const std::list<snkPoint>& wall)
{
    snkPoint food;
    food.mCol = GRN_BLACK;
    food.mSym = mFoodSym;

    auto comparator = [&food] (const snkPoint & point)
    {
        return (point.mX == food.mX) && (point.mY == food.mY);
    };

    bool isBody = false;
    bool isWall = false;

    do
    {
        food.mX = (std::rand() % (mW - 1)) + 1;
        food.mY = (std::rand() % (mH - 1)) + 1;
        isBody = std::find_if(body.begin(), body.end(), comparator) != body.end();
        isWall = std::find_if(wall.begin(), wall.end(), comparator) != wall.end();
    }
    while (isBody || isWall);

    return food;
}

void snkLevel::Move(std::list<snkPoint>& wall, milliseconds currTime)
{
    milliseconds delta = currTime - mPrevTime;

    if (delta.count() < WALL_SPEED)
    {
        return;
    }

    mPrevTime = currTime;

    if (7 == mLevelNum)
    {
        MoveH();
        wall = mWallMoveH;
    }
    else if (8 == mLevelNum)
    {
        MoveV();
        wall = mWallMoveV;
    }
    else if (9 == mLevelNum)
    {
        wall.clear();
        MoveH();
        MoveV();
        wall.insert(wall.end(), mWallMoveH.begin(), mWallMoveH.end());
        wall.insert(wall.end(), mWallMoveV.begin(), mWallMoveV.end());
    }
}

int snkLevel::GetLevel()
{
    return mSubLevel + mLevelNum * 10;
}

void snkLevel::LevelUp()
{
    ++mLevelNum;

    if (mLevelNum > 9)
    {
        mIsWin = true;
    }
}

void snkLevel::SubLeveUp()
{
    ++mSubLevel;

    if (mSubLevel > 9)
    {
        mSubLevel = 0;
    }
}

bool snkLevel::IsWin()
{
    return mIsWin;
}

void snkLevel::hLine(std::list<snkPoint>& wall)
{
    int y = mH / 2;
    int x = (mW / 2 - 1) - mW / 4;

    for (int i = 0; i < (mW / 2) + 2; ++i)
    {
        wall.emplace_back(snkPoint(x + i, y, mWallSym, RED_BLACK));
    }
}

void snkLevel::vLine(std::list<snkPoint>& wall)
{
    int y = (mH / 2 - 1) - mH / 4;
    int x = mW / 2;

    for (int i = 0; i < (mH / 2) + 2; ++i)
    {
        wall.emplace_back(snkPoint(x, y + i, mWallSym, RED_BLACK));
    }
}

void snkLevel::hDash(std::list<snkPoint>& wall)
{
    /* Horizontal line */
    int8_t space = 6;
    int8_t y = mH / 2;
    int8_t x = 0;
    int8_t limit = (mW / 2) - (space - 1);

    for (int8_t i = 0; i < limit; ++i)
    {
        wall.emplace_back(snkPoint(x + i, y, mWallSym, RED_BLACK));
    }

    x = (mW / 2) + space;

    for (int8_t i = 0; i < limit; ++i)
    {
        wall.emplace_back(snkPoint(x + i, y, mWallSym, RED_BLACK));
    }
}

void snkLevel::vDash(std::list<snkPoint>& wall)
{
    /* Vertical line */
    int8_t space = 4;
    int8_t y = 0;
    int8_t x = mW / 2;
    int8_t limit = (mH / 2) - (space - 1);

    for (int8_t i = 0; i < limit; ++i)
    {
        wall.emplace_back(snkPoint(x, y + i, mWallSym, RED_BLACK));
    }

    y = (mH / 2) + space;

    for (int8_t i = 0; i < limit; ++i)
    {
        wall.emplace_back(snkPoint(x, y + i, mWallSym, RED_BLACK));
    }
}

void snkLevel::hmLine(std::list<snkPoint>& wall)
{
    int y = mH / 2;
    int x = (mW / 2) - 2;

    for (int i = 0; i < (mW / 2) - 10; ++i)
    {
        wall.emplace_back(snkPoint(x + i, y, mWallSym, RED_BLACK));
    }
}

void snkLevel::vmLine(std::list<snkPoint>& wall)
{
    int y = (mH / 2) - 1;
    int x = mW / 2;

    for (int i = 0; i < (mH / 2) - 4; ++i)
    {
        wall.emplace_back(snkPoint(x, y + i, mWallSym, RED_BLACK));
    }
}

void snkLevel::MoveH()
{
    std::list<snkPoint>& wall = mWallMoveH;
    snkPoint head;

    if (mIsMoveLeft)
    {
        head = wall.front();
        head.mX -= 1;

        if (head.mX < 0)
        {
            mIsMoveLeft = false;
        }
        else
        {
            wall.pop_back();
            wall.push_front(head);
        }
    }
    else
    {
        head = wall.back();
        head.mX += 1;

        if (head.mX >= mW)
        {
            mIsMoveLeft = true;
        }
        else
        {
            wall.pop_front();
            wall.push_back(head);
        }
    }
}

void snkLevel::MoveV()
{
    std::list<snkPoint>& wall = mWallMoveV;
    snkPoint head;

    if (mIsMoveDown)
    {
        head = wall.back();
        head.mY += 1;

        if (head.mY >= mH)
        {
            mIsMoveDown = false;
        }
        else
        {
            wall.pop_front();
            wall.push_back(head);
        }
    }
    else
    {
        head = wall.front();
        head.mY -= 1;

        if (head.mY < 0)
        {
            mIsMoveDown = true;
        }
        else
        {
            wall.pop_back();
            wall.push_front(head);
        }
    }
}
