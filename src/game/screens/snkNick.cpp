/**
 * @file      snkNick.cpp
 * @brief     Contains implementation of class for input nickname screen.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      09/01/2019
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

    AddStrToBuf(to_snk_string("Enter Your Nickname"), 0);

    const int fieldPos = 3;

    /* Top of nickname frame */
    AddStrToBuf(GenFrameLine(MAX_NICK_SIZE + 2, ULC, HLN, URC), fieldPos - 1);

    /* Middle of nickname frame */
    AddStrToBuf(GenFrameLine(MAX_NICK_SIZE + 2, VLN, ' ', VLN), fieldPos);

    /* Bottom of nickname frame */
    AddStrToBuf(GenFrameLine(MAX_NICK_SIZE + 2, LLC, HLN, LRC), fieldPos + 1);
    
    const int col = (mW / 2) - ((MAX_NICK_SIZE + 2) / 2) + 1;
    AddStrToBuf(to_snk_string(mNickname), fieldPos, col);

    AddStrToBar(to_snk_string("Press END key to exit"), 0);
}
