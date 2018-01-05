#include "snkGame.h"

using namespace std::chrono;

void snkGame::Init(int w, int h)
{
    snkState::Construct(w, h);

    /* Initialize time */
    mTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    /* Initialize character state */
    mSnake.Init(w, h, ACS_BULLET);

    mLevel.Init(w, h, '+', '#');

    /* Generate initial food position */
    mFood = mLevel.GenFood(mSnake.GetBody());

    mScore = 0;
}

State snkGame::Update(int key)
{
    State ret = State::GAME;

    milliseconds curr = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    milliseconds delta = curr - mTime;

    /* Change data according to pressed key */
    switch (key)
    {
        case KEY_UP:
        {
            mSnake.SetDir(Dir::UP);
            break;
        }

        case KEY_RIGHT:
        {
            mSnake.SetDir(Dir::RT);
            break;
        }

        case KEY_LEFT:
        {
            mSnake.SetDir(Dir::LF);
            break;
        }

        case KEY_DOWN:
        {
            mSnake.SetDir(Dir::DN);
            break;
        }

        case KEY_END:
        {
            /* Reset snake states before exit to Main menu */
            mSnake.Reset();
            ret = State::MENU;
            break;
        }

        default:
        {
            break;
        }
    }

    if ( !mSnake.IsGameOver() && (delta.count() > mSnake.GetSpeed()) )
    {
        mTime = curr;

        mSnake.Move(mFood);
    }

    Refresh();

    return ret;
}

void snkGame::Refresh()
{
    ClearBuf();

    if (mSnake.IsGameOver())
    {
        std::string str = "GAME OVER";
        AddStr(str, mH / 2 - 1);

        str = "Press END key to exit!";
        AddStr(str, mH / 2 + 1);
    }
    else
    {
        /* Generate new food position */
        if (mSnake.IsFed())
        {
            mFood = mLevel.GenFood(mSnake.GetBody());
        }

        std::list<snkPoint> body = mSnake.GetBody();

        int x = 0;
        int y = 0;

        x = mFood.mX;
        y = mFood.mY;

        mBuf[y][x] = mFood;

        for (const auto& point : body)
        {
            x = point.mX;
            y = point.mY;

            mBuf[y][x] = point;
        }
    }

    std::string score(mNickname);
    score += std::string(": ");
    score += std::to_string(mScore);
    AddStrToBar(score, 0);
}
