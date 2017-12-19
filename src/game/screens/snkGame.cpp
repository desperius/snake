#include "snkGame.h"

using namespace std::chrono;

void snkGame::Init(int w, int h)
{
    snkState::Construct(w, h);

    /* Initialize time */
    mTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    /* Initialize character state */
    mSnake.Init(w, h, '*');

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

        case '\r':
        case '\n':
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
        mSnake.Move();
        Refresh();
    }

    return ret;
}

void snkGame::Refresh()
{
    ClearBuf();

    if (mSnake.IsGameOver())
    {
        std::string str = "GAME OVER";
        AddStr(str, mH / 2 - 1);

        str = "Press Enter to exit!";
        AddStr(str, mH / 2 + 1);
    }
    else
    {
        std::list<snkPoint> body = mSnake.GetBody();

        for (const auto& point : body)
        {
            int x = point.mX;
            int y = point.mY;

            mBuf[y][x] = point;
        }
    }

    std::string score(mNickname);
    score += std::string(": ");
    score += std::to_string(mScore);
    AddStrToBar(score, 0);
}
