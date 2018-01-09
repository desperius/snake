#include "snkState.h"

const snkField& snkState::GetGameField()
{
    return mBuf;
}

const snkField& snkState::GetScoreField()
{
    return mBar;
}

std::string snkState::GetNickname()
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
    for (int i = 0; i < mH; ++i)
    {
        for (int j = 0; j < mW; ++j)
        {
            mBuf[i][j].mSym = ' ';
        }

        mBuf[i][mW].mSym = '\0';
    }

    for (int j = 0; j < mW; ++j)
    {
        mBar[0][j].mSym = ' ';
    }

    mBar[0][mW].mSym = '\0';
}

void snkState::AddStr(const std::string& text, int row, int col)
{
    std::vector<chtype> data(text.begin(), text.end());

    AddTxt(data.data(), data.size(), row, col);
}

void snkState::AddTxt(const chtype* text, int size, int row, int col)
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
        mBuf[row][pos + i].mSym = text[i];
        mBuf[row][pos + i].mCol = WHT_BLACK;
    }
}

void snkState::AddStrToBar(const std::string& text, int row, int col)
{
    std::vector<chtype> data(text.begin(), text.end());

    AddTxtToBar(data.data(), data.size(), row, col);
}

void snkState::AddTxtToBar(const chtype* text, int size, int row, int col)
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
        mBar[row][pos + i].mSym = text[i];
    }
}
