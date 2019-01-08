/**
 * @file      snkState.cpp
 * @brief     Contains implementation of base class for game state.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      08/01/2019
 * @copyright GNU Public License
 */

#include "snkState.h"

snkString to_snk_string(std::string txt)
{
    return {txt.begin(), txt.end()};
}

const snkField& snkState::GetGameField() const
{
    return mBuf;
}

const snkField& snkState::GetScoreField() const
{
    return mBar;
}

std::string snkState::GetNickname() const
{
    return mNickname;
}

void snkState::SetNickname(const std::string& nickname)
{
    mNickname = nickname;
}

void snkState::Construct(int w, int h)
{
    mBuf = std::vector<std::vector<snkPoint>>(h + 1, std::vector<snkPoint>(w + 1));
    mBar = std::vector<std::vector<snkPoint>>(1, std::vector<snkPoint>(w + 1));
    mW = w;
    mH = h;
    ClearBuf();
}

void snkState::ClearBuf()
{
    /* Clear game field */
    for (int i = 0; i < mH; ++i)
    {
        for (int j = 0; j < mW; ++j)
        {
            mBuf[i][j].mSym = ' ';
            mBuf[i][j].mCol = WHT_BLACK;
        }

        mBuf[i][mW].mSym = '\0';
    }

    /* Clear status bar */
    for (int j = 0; j < mW; ++j)
    {
        mBar[0][j].mSym = ' ';
        mBar[0][j].mCol = WHT_BLACK;
    }

    mBar[0][mW].mSym = '\0';
}

void snkState::AddStrToBuf(const snkString& text, int row, int col)
{
    AddTxt(mBuf, text.data(), text.size(), row, col);
}

void snkState::AddStrToBar(const snkString& text, int row, int col)
{
    AddTxt(mBar, text.data(), text.size(), row, col);
}

void snkState::AddTxt(snkField& buf, const chtype* text, int size, int row, int col)
{
    int pos = 0;

    if (0 == col)
    {
        pos = (mW - size) / 2;
    }
    else
    {
        pos = col;
    }

    for (int i = 0; i < size; ++i)
    {
        buf[row][pos + i].mSym = text[i];
        buf[row][pos + i].mCol = WHT_BLACK;
    }
}
