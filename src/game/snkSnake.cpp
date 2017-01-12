#include "snkSnake.h"

void snkSnake::Init(int w, int h)
{
   int cx = w / 2;
   int cy = h / 2;

   mBody.push_back(snkPoint(cx, cy, Dir::UP));
   mBody.push_back(snkPoint(cx, cy + 1, Dir::UP));
   mBody.push_back(snkPoint(cx, cy + 2, Dir::UP));
}

void snkSnake::Move()
{
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

   mBody.pop_back();
   mBody.push_front(head);
}

void snkSnake::SetDir(Dir dir)
{
   mDir = dir;
}

int snkSnake::GetSpeed()
{
   return mSpeed;
}
