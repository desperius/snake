#ifndef _SNK_STATE_H_
#define _SNK_STATE_H_

#include "curses.h"

#include <string>
#include <vector>

typedef std::vector<std::vector<char>> snkField;

enum class State : int
{
   MENU  = 1,
   START = MENU  + 2,
   ABOUT = START + 2,
   EXIT  = ABOUT + 2
};

class snkState
{
public:
   snkState() = default;
   virtual ~snkState() = default;

   void ClearBuf();

   virtual State Update(int key) = 0;

protected:
   void Init(snkField& buf, int w, int h);
   virtual void Refresh() = 0;

protected:
   snkField* mBuf;
   int mW {0};
   int mH {0};
};

#endif /* _SNK_STATE_H_ */
