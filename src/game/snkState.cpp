#include "snkState.h"

void snkState::Init(snkField& buf, int w, int h)
{
   mBuf = &buf;
   mW = w;
   mH = h;
}

void snkState::ClearBuf()
{
   for (int i = 0; i < mH; ++i)
   {
      for (int j = 0; j < mW; ++j)
      {
         /* In such way pointer to two dimensional vector must be used */
         (*mBuf)[i][j] = ' ';
      }

      (*mBuf)[i][mW] = '\0';
   }
}
