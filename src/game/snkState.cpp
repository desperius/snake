#include "snkState.h"

const snkField& snkState::GetGameField()
{
    return mBuf;
}

void snkState::Construct(int w, int h)
{
    mBuf = std::vector<std::vector<snkPoint>>(h + 1, std::vector<snkPoint>(w + 1));
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
}

void snkState::CreateItem(const char* text, int size, int row)
{
    std::vector<chtype> data(size);

    for (int i = 0; i < size; ++i)
    {
        data[i] = text[i];
    }

    CreateItem(data.data(), data.size(), row);
}

void snkState::CreateItem(const chtype* text, int size, int row)
{
    int pos = (mW - size) / 2;

    for (int i = 0; i < size; ++i)
    {
        mBuf[row][pos + i].mSym = text[i];
    }
}
