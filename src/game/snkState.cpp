#include "snkState.h"

const snkField& snkState::GetGameField()
{
   return mBuf;
}

void snkState::Construct(int w, int h)
{
   mBuf = std::vector<std::vector<char>>(h + 1, std::vector<char>(w + 1));
   mW = w;
   mH = h;
}

void snkState::ClearBuf()
{
   for (int i = 0; i < mH; ++i)
   {
      for (int j = 0; j < mW; ++j)
      {
         mBuf[i][j] = ' ';
      }

      mBuf[i][mW] = '\0';
   }
}

void snkState::CreateItem(const char* text, int size, int row)
{
   int pos = (mW - size) / 2;

   for (int i = 0; i < size; ++i)
   {
      mBuf[row][pos + i] = text[i];
   }
}
