/**
 * @file      snkMenu.cpp
 * @brief     Contains implementation of class for main menu.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      08/01/2019
 * @copyright GNU Public License
 */

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

    AddStrToBuf(to_snk_string("S N A K E"), 0);

    /* Create frame for menu item */
    chtype ulc = ACS_ULCORNER;
    chtype urc = ACS_URCORNER;
    chtype hln = ACS_HLINE;
    chtype vln = ACS_VLINE;
    chtype llc = ACS_LLCORNER;
    chtype lrc = ACS_LRCORNER;

    snkString txt = {ulc, hln, hln, hln, hln, hln, hln, hln, urc};
    AddStrToBuf(txt, static_cast<int>(mActive) - 1);

    txt = {vln, ' ', ' ', ' ', ' ', ' ', ' ', ' ', vln};
    AddStrToBuf(txt, static_cast<int>(mActive));

    txt = {llc, hln, hln, hln, hln, hln, hln, hln, lrc};
    AddStrToBuf(txt, static_cast<int>(mActive) + 1);

    /* Create menu items */
    AddStrToBuf(to_snk_string("START"), static_cast<int>(State::GAME));
    AddStrToBuf(to_snk_string("RECORDS"), static_cast<int>(State::RECS));
    AddStrToBuf(to_snk_string("EXIT!"), static_cast<int>(State::EXIT));

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
