/**
 * @brief Contains implementation of class for levels generation and management
 */

#include "snkLevel.hpp"
#include <algorithm>
#include <random>

using namespace std::chrono;

void snkLevel::Init(const int w, const int h, const chtype food_sym, const chtype wall_sym)
{
    mW = w;
    mH = h;
    mFoodSym = food_sym;
    mWallSym = wall_sym;

    mPrevTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
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

snkPoint snkLevel::GenFood(const std::list<snkPoint>& body, const std::list<snkPoint>& wall) const
{
    snkPoint food;
    food.mCol = GRN_BLACK;
    food.mSym = mFoodSym;

    auto comparator = [&food] (const snkPoint & point)
    {
        return (point.mX == food.mX) && (point.mY == food.mY);
    };

    thread_local std::mt19937 engine{std::random_device{}()};
    std::uniform_int_distribution<int> randomX(1, mW - 1);
    std::uniform_int_distribution<int> randomY(1, mH - 1);

    bool isBody;
    bool isWall;

    do
    {
        food.mX = randomX(engine);
        food.mY = randomY(engine);
        isBody = std::find_if(body.begin(), body.end(), comparator) != body.end();
        isWall = std::find_if(wall.begin(), wall.end(), comparator) != wall.end();
    }
    while (isBody || isWall);

    return food;
}

void snkLevel::Move(std::list<snkPoint>& wall, const milliseconds currTime)
{
    const milliseconds delta = currTime - mPrevTime;

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

int snkLevel::GetLevel() const
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

bool snkLevel::IsWin() const
{
    return mIsWin;
}

void snkLevel::hLine(std::list<snkPoint>& wall) const
{
    const int y = mH / 2;
    const int x = (mW / 2 - 1) - mW / 4;

    for (int i = 0; i < (mW / 2) + 2; ++i)
    {
        wall.emplace_back(x + i, y, mWallSym, RED_BLACK);
    }
}

void snkLevel::vLine(std::list<snkPoint>& wall) const
{
    const int y = (mH / 2 - 1) - mH / 4;
    const int x = mW / 2;

    for (int i = 0; i < (mH / 2) + 2; ++i)
    {
        wall.emplace_back(x, y + i, mWallSym, RED_BLACK);
    }
}

void snkLevel::hDash(std::list<snkPoint>& wall) const
{
    /* Horizontal line */
    constexpr int8_t space = 6;
    const int y = mH / 2;
    int x = 0;
    const int limit = (mW / 2) - (space - 1);

    for (int i = 0; i < limit; ++i)
    {
        wall.emplace_back(x + i, y, mWallSym, RED_BLACK);
    }

    x = (mW / 2) + space;

    for (int i = 0; i < limit; ++i)
    {
        wall.emplace_back(x + i, y, mWallSym, RED_BLACK);
    }
}

void snkLevel::vDash(std::list<snkPoint>& wall) const
{
    /* Vertical line */
    constexpr int8_t space = 4;
    int y = 0;
    const int x = mW / 2;
    const int limit = (mH / 2) - (space - 1);

    for (int i = 0; i < limit; ++i)
    {
        wall.emplace_back(x, y + i, mWallSym, RED_BLACK);
    }

    y = (mH / 2) + space;

    for (int i = 0; i < limit; ++i)
    {
        wall.emplace_back(x, y + i, mWallSym, RED_BLACK);
    }
}

void snkLevel::hmLine(std::list<snkPoint>& wall) const
{
    const int y = mH / 2;
    const int x = (mW / 2) - 2;

    for (int i = 0; i < (mW / 2) - 10; ++i)
    {
        wall.emplace_back(x + i, y, mWallSym, RED_BLACK);
    }
}

void snkLevel::vmLine(std::list<snkPoint>& wall) const
{
    const int y = (mH / 2) - 1;
    const int x = mW / 2;

    for (int i = 0; i < (mH / 2) - 4; ++i)
    {
        wall.emplace_back(x, y + i, mWallSym, RED_BLACK);
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
