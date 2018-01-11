#include "snkLevel.h"
#include <algorithm>
#include <cstdlib>

void snkLevel::Init(int w, int h, chtype food_sym, chtype wall_sym)
{
    mW = w;
    mH = h;
    mFoodSym = food_sym;
    mWallSym = wall_sym;
}

std::list<snkPoint> snkLevel::GenWall(int level)
{
    std::list<snkPoint> wall;

    if (level == 2)
    {
        hLine(wall);
    }
    else if (level == 2)
    {
        vLine(wall);
    }
    else if (level == 4)
    {
        hLine(wall);
        vLine(wall);
    }
    else if (level == 1)
    {
        /* Horizontal line */
        int y = mH / 2;
        int x = 0;

        for (int i = 0; i < (mW / 2) - 2; ++i)
        {
            wall.emplace_back(snkPoint(x + i, y, mWallSym, RED_BLACK));
        }

        x = (mW / 2) + 3;

        for (int i = 0; i < (mW / 2) - 2; ++i)
        {
            wall.emplace_back(snkPoint(x + i, y, mWallSym, RED_BLACK));
        }

        /* Vertical line */
        y = 0;
        x = mW / 2;

        for (int i = 0; i < (mH / 2) - 2; ++i)
        {
            wall.emplace_back(snkPoint(x, y + i, mWallSym, RED_BLACK));
        }

        y = (mH / 2) + 3;

        for (int i = 0; i < (mH / 2) - 2; ++i)
        {
            wall.emplace_back(snkPoint(x, y + i, mWallSym, RED_BLACK));
        }
    }

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
