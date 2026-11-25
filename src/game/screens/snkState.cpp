/**
 * @brief Contains implementation of base class for game state
 */

#include "snkState.hpp"

chtype snkState::ULC = 0;
chtype snkState::URC = 0;
chtype snkState::HLN = 0;
chtype snkState::VLN = 0;
chtype snkState::LLC = 0;
chtype snkState::LRC = 0;

snkString to_snk_string(std::string txt)
{
    return { txt.begin(), txt.end() };
}

snkState::snkState(const int w, const int h)
    : mW(w)
    , mH(h)
{
    ULC = ACS_ULCORNER;
    URC = ACS_URCORNER;
    HLN = ACS_HLINE;
    VLN = ACS_VLINE;
    LLC = ACS_LLCORNER;
    LRC = ACS_LRCORNER;

    mBuf = std::vector<std::vector<snkPoint>>(mH + 1, std::vector<snkPoint>(mW + 1));
    mBar = std::vector<std::vector<snkPoint>>(1, std::vector<snkPoint>(mW + 1));
    ClearBuf();
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

void snkState::ClearBuf()
{
    // Clear game field
    for (int y = 0; y < mH; ++y)
    {
        for (int x = 0; x < mW; ++x)
        {
            mBuf[y][x].mSym = ' ';
            mBuf[y][x].mCol = WHT_BLACK;
        }

        mBuf[y][mW].mSym = '\0';
    }

    // Clear status bar
    for (int x = 0; x < mW; ++x)
    {
        mBar[0][x].mSym = ' ';
        mBar[0][x].mCol = WHT_BLACK;
    }

    mBar[0][mW].mSym = '\0';
}

void snkState::AddStrToBuf(const snkString& text, const int row, const int col)
{
    AddTxt(mBuf, text.data(), text.size(), row, col);
}

void snkState::AddStrToBar(const snkString& text, const int row, const int col)
{
    AddTxt(mBar, text.data(), text.size(), row, col);
}

snkString snkState::GenFrameLine(const int len, const chtype l, const chtype m, const chtype r)
{
    snkString line(len, ' ');

    line[0] = l;

    for (int i = 1; i < len - 1; ++i)
    {
        line[i] = m;
    }

    line[len - 1] = r;

    return line;
}

void snkState::AddTxt(snkField &buf, const chtype *text, const size_t size, const int row, const int col) const
{
    int pos;

    if (0 == col)
    {
        pos = (mW - static_cast<int>(size)) / 2;
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
