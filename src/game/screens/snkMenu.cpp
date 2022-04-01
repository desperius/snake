/**
 * @file      snkMenu.cpp
 * @brief     Contains implementation of class for main menu.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.1
 * @date      01/04/2022
 * @copyright GNU Public License
 */

#include "snkMenu.h"

namespace
{

int GetMenuItemPosition(State Item)
{
    return 2 * static_cast<int>(Item) + 1;
}

State& operator++(State& StateValue)
{
    const int NumValue = static_cast<int>(StateValue) + 1;
    StateValue = static_cast<State>(NumValue % static_cast<int>(State::MAXN));
    return StateValue;
}

State& operator--(State& StateValue)
{
    const int NumValue = static_cast<int>(StateValue) - 1;
    StateValue = static_cast<State>(NumValue % static_cast<int>(State::MAXN));
    return StateValue;
}

}

State snkMenu::Update(int key)
{
    State ret = State::MENU;

    /* Change data according to pressed key */
    switch (key)
    {
        case KEY_UP:
        {
            if (mActive != State::GAME)
            {
                --mActive;
                Refresh();
            }

            break;
        }

        case KEY_DOWN:
        {
            if (mActive != State::EXIT)
            {
                ++mActive;
                Refresh();
            }

            break;
        }

        case '\r':
        case '\n':
        {
            if (State::GAME == mActive)
            {
                /* If player want to start the game, he should enter the nickname first */
                ret = State::NICK;
            }
            else
            {
                ret = mActive;
            }

            break;
        }

        default:
        {
            Refresh();
            break;
        }
    }

    return ret;
}

void snkMenu::Refresh()
{
    ClearBuf();

    AddStrToBuf(to_snk_string("S N A K E"), 0);

    int Pos = GetMenuItemPosition(mActive);

    /* Top of menu item frame */
    AddStrToBuf(GenFrameLine(MAX_FRAME_SIZE, ULC, HLN, URC), Pos - 1);
    
    /* Middle of menu item frame */
    AddStrToBuf(GenFrameLine(MAX_FRAME_SIZE, VLN, ' ', VLN), Pos);
    
    /* Bottom of menu item frame */
    AddStrToBuf(GenFrameLine(MAX_FRAME_SIZE, LLC, HLN, LRC), Pos + 1);

    /* Create menu items */
    AddStrToBuf(to_snk_string("START"), GetMenuItemPosition(State::GAME));
    AddStrToBuf(to_snk_string("RECORDS"), GetMenuItemPosition(State::RECS));
    AddStrToBuf(to_snk_string("EXIT!"), GetMenuItemPosition(State::EXIT));

    std::string ver = "version ";
    ver += std::to_string(MAJOR) + ".";
    ver += std::to_string(MINOR);
    AddStrToBuf(to_snk_string(ver), mH - 1);

    if (State::GAME == mActive)
    {
        AddStrToBar(to_snk_string("Starts a new game"), 0);
    }
    else if (State::RECS == mActive)
    {
        AddStrToBar(to_snk_string("Shows last 10 best scores"), 0);
    }
    else if (State::EXIT == mActive)
    {
        AddStrToBar(to_snk_string("Stay, please! :)"), 0);
    }
}
