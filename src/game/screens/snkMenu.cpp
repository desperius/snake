#include "snkMenu.h"

void snkMenu::Init(int w, int h)
{
    snkState::Construct(w, h);
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
                int menu_item = static_cast<int>(mActive) - 2;
                mActive = static_cast<State>(menu_item);
                Refresh();
            }

            break;
        }

        case KEY_DOWN:
        {
            if (mActive != State::EXIT)
            {
                int menu_item = static_cast<int>(mActive) + 2;
                mActive = static_cast<State>(menu_item);
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

    std::string str = "S N A K E";
    AddStr(str, 0);

    /* Create frame for menu item */
    chtype ulc = ACS_ULCORNER;
    chtype urc = ACS_URCORNER;
    chtype hln = ACS_HLINE;
    chtype vln = ACS_VLINE;
    chtype llc = ACS_LLCORNER;
    chtype lrc = ACS_LRCORNER;

    std::vector<chtype> txt = {ulc, hln, hln, hln, hln, hln, hln, hln, urc};
    AddTxt(txt.data(), txt.size(), static_cast<int>(mActive) - 1);

    txt = {vln, ' ', ' ', ' ', ' ', ' ', ' ', ' ', vln};
    AddTxt(txt.data(), txt.size(), static_cast<int>(mActive));

    txt = {llc, hln, hln, hln, hln, hln, hln, hln, lrc};
    AddTxt(txt.data(), txt.size(), static_cast<int>(mActive) + 1);

    /* Create menu items */
    str = "START";
    AddStr(str, static_cast<int>(State::GAME));

    str = "RECORDS";
    AddStr(str, static_cast<int>(State::RECS));

    str = "EXIT!";
    AddStr(str, static_cast<int>(State::EXIT));

    str = "version ";
    str += std::to_string(MAJOR) + ".";
    str += std::to_string(MINOR);
    AddStr(str, mH - 1);

    if (State::GAME == mActive)
    {
        AddStrToBar(std::string("Starts a new game"), 0);
    }
    else if (State::RECS == mActive)
    {
        AddStrToBar(std::string("Shows last 10 best scores"), 0);
    }
    else if (State::EXIT == mActive)
    {
        AddStrToBar(std::string("Stay, please! :)"), 0);
    }
}
