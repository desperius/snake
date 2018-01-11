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

    /* Generate wall positions */
    mWall = mLevel.GenWall(mLevelNum);

    /* Generate initial food position */
    mFood = mLevel.GenFood(mSnake.GetBody(), mWall);

    mScore = 0;
}

State snkGame::Update(int key)
{
    State ret = State::GAME;

    milliseconds curr = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    milliseconds delta = curr - mTime;

    if (mIsLvlStart)
    {
        AddStr("LEVEL " + std::to_string(mLevelNum), mH / 2 - 1);
        AddStr("Press Enter to start", mH / 2 + 1);

        if ('\n' == key || '\r' == key)
        {
            mIsLvlStart = false;
        }
        else
        {
            return ret;
        }
    }

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

    if (!mSnake.IsGameOver() && (delta.count() > mSnake.GetSpeed()))
    {
        mTime = curr;

        mSnake.Move(mFood, mWall);
    }

    Refresh();

    return ret;
}

void snkGame::Refresh()
{
    //ClearBuf();

    if (mSnake.IsGameOver())
    {
        std::string str = "GAME OVER";
        AddStr(str, mH / 2 - 1);

        str = "Press END key to exit!";
        AddStr(str, mH / 2 + 1);
    }
    else
    {
        ClearBuf();

        if (0 == mFoodNum)
        {
            mIsLvlStart = true;
            mSnake.Reset();
            ++mLevelNum;
            mFoodNum = 3;

            if (mLevelNum % 10 == 0)
            {
                mSnake.ResetSpeed();
            }
            else
            {
                mSnake.SetSpeed(mSnake.GetSpeed() - 50);
            }

            mWall = mLevel.GenWall(mLevelNum);
            return;
        }

        /* Generate new food position */
        if (mSnake.GetIsFed())
        {
            mFood = mLevel.GenFood(mSnake.GetBody(), mWall);
            mSnake.SetIsFed(false);
            --mFoodNum;
            ++mScore;
        }

        std::list<snkPoint> body = mSnake.GetBody();

        int x = mFood.mX;
        int y = mFood.mY;

        /* Draw food position */
        mBuf[y][x] = mFood;

        /* Draw wall position */
        for (const auto& point : mWall)
        {
            x = point.mX;
            y = point.mY;

            mBuf[y][x] = point;
        }

        /* Draw snake position */
        for (const auto& point : body)
        {
            x = point.mX;
            y = point.mY;

            mBuf[y][x] = point;
        }
    }

    std::string bar(mNickname);
    bar += std::string(": ");
    bar += std::to_string(mScore);
    bar += std::string("   Level: ");
    bar += std::to_string(mLevelNum);
    AddStrToBar(bar, 0);
}
