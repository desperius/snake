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
            if (mActive != State::START)
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
            ret = mActive;
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

    std::vector<chtype> text = {'S', ' ', 'N', ' ', 'A', ' ', 'K', ' ', 'E'};
    CreateItem(text.data(), text.size(), 0);

    /* Create frame for menu item */
    chtype ulc = ACS_ULCORNER;
    chtype urc = ACS_URCORNER;
    chtype hln = ACS_HLINE;
    chtype vln = ACS_VLINE;
    chtype llc = ACS_LLCORNER;
    chtype lrc = ACS_LRCORNER;

    text = {ulc, hln, hln, hln, hln, hln, hln, hln, urc};
    CreateItem(text.data(), text.size(), static_cast<int>(mActive) - 1);

    text = {vln, ' ', ' ', ' ', ' ', ' ', ' ', ' ', vln};
    CreateItem(text.data(), text.size(), static_cast<int>(mActive));

    text = {llc, hln, hln, hln, hln, hln, hln, hln, lrc};
    CreateItem(text.data(), text.size(), static_cast<int>(mActive) + 1);

    /* Create menu items */
    text = {'S', 'T', 'A', 'R', 'T'};
    CreateItem(text.data(), text.size(), static_cast<int>(State::START));

    text = {'A', 'B', 'O', 'U', 'T'};
    CreateItem(text.data(), text.size(), static_cast<int>(State::ABOUT));

    text = {'E', 'X', 'I', 'T', '!'};
    CreateItem(text.data(), text.size(), static_cast<int>(State::EXIT));

    std::string version = "version 1.0";
    CreateItem(version.c_str(), version.length(), mH - 1);
}
