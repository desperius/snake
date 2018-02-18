/**
 * @file      snkNick.cpp
 * @brief     Contains implementation of class for input nickname screen.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      16/02/2018
 * @copyright GNU Public License
 */

#include "snkNick.h"
#include <ctype.h>

#ifndef VK_BACK
#define VK_BACK 0x8
#endif

void snkNick::Init(int w, int h)
{
    snkState::Construct(w, h);
}

State snkNick::Update(int key)
{
    State ret = State::NICK;

    if (isalpha(key) && (mNickname.size() < MAX_NICK_SIZE))
    {
        mNickname += static_cast<char>(key);
    }

    /* Change data according to pressed key */
    switch (key)
    {
        case KEY_BACKSPACE:
        case VK_BACK: /* Windows Virtual-Key code */
        {
            if (mNickname.length() > 0)
            {
                mNickname.pop_back();
            }

            break;
        }

        case KEY_END:
        {
            ret = State::MENU;
            break;
        }

        case '\r':
        case '\n':
        {
            if (!mNickname.empty())
            {
                ret = State::GAME;
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

void snkNick::Refresh()
{
    ClearBuf();

    std::string str = "Enter Your Nickname";
    AddStr(str, 0);

    /* Create frame for nickname input field */
    chtype ulc = ACS_ULCORNER;
    chtype urc = ACS_URCORNER;
    chtype hln = ACS_HLINE;
    chtype vln = ACS_VLINE;
    chtype llc = ACS_LLCORNER;
    chtype lrc = ACS_LRCORNER;

    int fieldPos = 3;
    std::vector<chtype> line;

    /* Top of nickname frame */
    line = GenLine(ulc, hln, urc);
    AddTxt(line.data(), line.size(), fieldPos - 1);

    /* Middle of nickname frame */
    line = GenLine(vln, ' ', vln);
    AddTxt(line.data(), line.size(), fieldPos);

    /* Bottom of nickname frame */
    line = GenLine(llc, hln, lrc);
    AddTxt(line.data(), line.size(), fieldPos + 1);

    AddStr(mNickname, fieldPos, (mW / 2) - (line.size() / 2) + 1);

    str = "Press END key to exit";
    AddStrToBar(str, 0);
}

std::vector<chtype> snkNick::GenLine(chtype l, chtype m, chtype r)
{
    std::vector<chtype> line(MAX_NICK_SIZE + 2);

    line[0] = l;

    for (int i = 1; i <= MAX_NICK_SIZE; ++i)
    {
        line[i] = m;
    }

    line[MAX_NICK_SIZE + 1] = r;

    return line;
}
