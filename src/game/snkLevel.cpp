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

snkPoint snkLevel::GenFood(const std::list<snkPoint>& body)
{
    snkPoint food;
    food.mCol = GRN_BLACK;
    food.mSym = mFoodSym;

    auto comparator = [&food] (const snkPoint & point)
    {
        return (point.mX == food.mX) && (point.mY == food.mY);
    };

    do
    {
        food.mX = (std::rand() % (mW - 1)) + 1;
        food.mY = (std::rand() % (mH - 1)) + 1;
    }
    while (std::find_if(body.begin(), body.end(), comparator) != body.end());

    return food;
}
