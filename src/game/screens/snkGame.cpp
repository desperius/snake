#include "snkGame.h"

using namespace std::chrono;

void snkGame::Init(int w, int h)
{
    snkState::Construct(w, h);

    /* Initialize character state */
    mSnake.Init(w, h, ACS_BULLET);

    /* Initialize level */
    mLevel.Init(w, h, '+', '#');

    /* Generate wall positions */
    mWall = mLevel.GenWall();

    /* Generate initial food position */
    mFood = mLevel.GenFood(mSnake.GetBody(), mWall);

    /* Open database */
    mRecs.Connect();

    mScore = 0;
}

State snkGame::Update(int key)
{
    State ret = State::GAME;

    milliseconds currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    if (mLevel.IsWin())
    {
        AddStr("+     +   +   +     +", mH / 2 - 2);
        AddStr("+     +   +   + +   +", mH / 2 - 1);
        AddStr("+  +  +   +   +  +  +", mH / 2);
        AddStr("+  +  +   +   +   + +", mH / 2 + 1);
        AddStr(" +   +    +   +     +", mH / 2 + 2);

        if ('\n' == key || '\r' == key)
        {
            return State::MENU;
        }
        else
        {
            return ret;
        }
    }

    if (mIsStart)
    {
        AddStr("LEVEL " + std::to_string(mLevel.GetLevel()), mH / 2 - 1);
        AddStr("Press Enter to start", mH / 2 + 1);

        if ('\n' == key || '\r' == key)
        {
            mIsStart = false;
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

            /* Write score and nick in records table */
            mRecs.Write(mNickname, mScore);
            mRecs.Print();
            mRecs.Close();

            ret = State::MENU;
            break;
        }

        default:
        {
            break;
        }
    }

    if (!mSnake.IsGameOver())
    {
        mSnake.Move(mFood, mWall, currTime);
    }

    mLevel.Move(mWall, currTime);

    Refresh();

    return ret;
}

void snkGame::Refresh()
{
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

        /* All food at this level were eaten */
        if (0 == mFoodNum)
        {
            mLevel.SubLeveUp();
            mSnake.SetSpeed(mSnake.GetSpeed() - 50);

            if (mSnake.GetSpeed() <= 0)
            {
                mLevel.LevelUp();
                mSnake.ResetSpeed();
            }

            mIsStart = true;
            mSnake.Reset();
            mWall = mLevel.GenWall();
            mFoodNum = FOOD_MAX;

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

        /* Draw snake position */
        for (const auto& point : body)
        {
            x = point.mX;
            y = point.mY;

            mBuf[y][x] = point;
        }

        /* Draw wall position */
        for (const auto& point : mWall)
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
    bar += std::to_string(mLevel.GetLevel());
    AddStrToBar(bar, 0);
}
