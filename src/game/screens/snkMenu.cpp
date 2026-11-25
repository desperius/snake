/**
 * @brief     Contains implementation of class for main menu
 */

#include "snkMenu.hpp"

namespace
{

int GetMenuItemPosition(const State& item)
{
    return 2 * static_cast<int>(item) + 1;
}

State& operator++(State& stateValue)
{
    const int numValue = static_cast<int>(stateValue) + 1;
    stateValue = static_cast<State>(numValue % static_cast<int>(State::COUNT));
    return stateValue;
}

State& operator--(State& stateValue)
{
    const int numValue = static_cast<int>(stateValue) - 1;
    stateValue = static_cast<State>(numValue % static_cast<int>(State::COUNT));
    return stateValue;
}

}

State snkMenu::Update(const int key)
{
    auto ret = State::MENU;

    // Change data according to pressed key
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
                // If player want to start the game, he should enter the nickname first
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

    const int Pos = GetMenuItemPosition(mActive);

    // Top of menu item frame
    AddStrToBuf(GenFrameLine(MAX_FRAME_SIZE, ULC, HLN, URC), Pos - 1);
    
    // Middle of menu item frame
    AddStrToBuf(GenFrameLine(MAX_FRAME_SIZE, VLN, ' ', VLN), Pos);
    
    // Bottom of menu item frame
    AddStrToBuf(GenFrameLine(MAX_FRAME_SIZE, LLC, HLN, LRC), Pos + 1);

    // Create menu items
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
