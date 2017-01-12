#include "snkGame.h"

using namespace std::chrono;

void snkGame::Init(snkField& buf, int w, int h)
{
   snkState::Init(buf, w, h);

   /* Initialize time */
   mTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

   /* Initialize character state */
   mSnake.Init(w, h);
}

State snkGame::Update(int key)
{
   State ret = State::START;

   milliseconds curr = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
   milliseconds delta = curr - mTime;

   /* Change data according to pressed key */
   switch (key)
   {
      case KEY_UP:
      {
         mSnake.SetDir(Dir::UP);
         break;
      }

      case KEY_RIGHT:
      {
         mSnake.SetDir(Dir::RT);
         break;
      }

      case KEY_LEFT:
      {
         mSnake.SetDir(Dir::LF);
         break;
      }

      case KEY_DOWN:
      {
         mSnake.SetDir(Dir::DN);
         break;
      }

      case '\r':
      case '\n':
      {
         ret = State::MENU;
         break;
      }

      default:
      {
         break;
      }
   }

   if (delta.count() > mSnake.GetSpeed())
   {
      mTime = curr;
      mSnake.Move();
   }

   Refresh();

   return ret;
}

void snkGame::Refresh()
{
   ClearBuf();

   std::list<snkPoint> body = mSnake.GetBody();

   for (auto point : body)
   {
      int x = point.mX;
      int y = point.mY;

      (*mBuf)[y][x] = '*';
   }
}
