#include "snkSnake.h"
#include <algorithm>

void snkSnake::Init(int w, int h)
{
   mW = w;
   mH = h;

   Reset();
}

void snkSnake::Move()
{
   if (mGameOver)
   {
      return;
   }

   int x = mBody.front().mX;
   int y = mBody.front().mY;
   snkPoint head(x, y);

   switch (mDir)
   {
      case Dir::UP:
      {
         head.mY -= 1;
         break;
      }

      case Dir::DN:
      {
         head.mY += 1;
         break;
      }

      case Dir::RT:
      {
         head.mX += 1;
         break;
      }

      case Dir::LF:
      {
         head.mX -= 1;
         break;
      }

      default:
      {
         break;
      }
   }

   /* Reached right or left border */
   if (head.mX >= mW || head.mX < 0)
   {
      mGameOver = true;
   }

   /* Reached bottom or top border */
   if (head.mY >= mH || head.mY < 0)
   {
      mGameOver = true;
   }

   auto comparator = [&head] (const snkPoint& point)
   {
      return (point.mX == head.mX) && (point.mY == head.mY);
   };

   auto it = std::find_if(mBody.begin(), mBody.end(), comparator);

   /* Bite yourself :) */
   if (it != mBody.end())
   {
      mGameOver = true;
   }

   mBody.pop_back();
   mBody.push_front(head);
}

void snkSnake::SetDir(Dir dir)
{
   mDir = dir;
}

void snkSnake::Reset()
{
   int cx = mW / 2;
   int cy = mH / 2;

   mBody.clear();
   mBody.push_back(snkPoint(cx, cy, Dir::UP));
   mBody.push_back(snkPoint(cx, cy + 1, Dir::UP));
   mBody.push_back(snkPoint(cx, cy + 2, Dir::UP));

   mGameOver = false;

   // TODO: Only for check
   mBody.push_back(snkPoint(cx, cy + 3, Dir::UP));
   mBody.push_back(snkPoint(cx, cy + 4, Dir::UP));
   mBody.push_back(snkPoint(cx, cy + 5, Dir::UP));
}
