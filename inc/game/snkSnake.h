#ifndef _SNK_SNAKE_H_
#define _SNK_SNAKE_H_

#include <list>

enum class Dir : short
{
   UP,
   DN,
   RT,
   LF
};

struct snkPoint
{
   snkPoint(int x = 0, int y = 0, Dir vec = Dir::UP) :
      mX(x),
      mY(y),
      mVec(vec)
   {}

   ~snkPoint() = default;

   int mX;
   int mY;
   Dir mVec;
};

class snkSnake
{
public:
   snkSnake()  = default;
   ~snkSnake() = default;

   void Init(int w, int h);
   void Move();
   void SetDir(Dir dir);

   int GetSpeed()
   {
      return mSpeed;
   }

   std::list<snkPoint> GetBody()
   {
      return mBody;
   }

   bool IsGameOver()
   {
      return mGameOver;
   }

   void Reset();

private:
   std::list<snkPoint> mBody;
   int mW;
   int mH;
   Dir mDir {Dir::UP};
   int mSpeed {500};
   bool mGameOver {false};
};

#endif /* _SNK_SNAKE_H_ */
