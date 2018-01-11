#ifndef _SNK_LEVEL_H_
#define _SNK_LEVEL_H_

/* + food */
/* # wall */

#include <list>
#include "snkState.h"

class snkLevel
{
public:
    snkLevel() = default;
    ~snkLevel() = default;

    void Init(int w, int h, chtype food_sym, chtype wall_sym);
    std::list<snkPoint> GenWall(int level);
    snkPoint GenFood(const std::list<snkPoint>& body, const std::list<snkPoint>& wall);

private:
    void hLine(std::list<snkPoint>& wall);
    void vLine(std::list<snkPoint>& wall);

private:
    int mW = {0};
    int mH = {0};
    int mFoodCount;
    chtype mFoodSym;
    chtype mWallSym;
};

#endif /* _SNK_LEVEL_H_ */
