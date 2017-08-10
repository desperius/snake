#ifndef _SNK_STATE_H_
#define _SNK_STATE_H_

#include "curses.h"

#include <string>
#include <vector>

enum class State : int
{
    MENU  = 1,
    START = MENU  + 2,
    ABOUT = START + 2,
    EXIT  = ABOUT + 2
};

enum Color
{
    WHT_BLACK = 1,
    RED_BLACK = 2,
    GRN_BLACK = 3
};

struct snkPoint
{
    explicit snkPoint(int x = 0, int y = 0, chtype sym = ' ', Color col = WHT_BLACK)
        : mX(x)
        , mY(y)
        , mSym(sym)
        , mCol(col)
    {}

    ~snkPoint() = default;

    int mX;
    int mY;
    chtype mSym;
    Color  mCol;
};

typedef std::vector<std::vector<snkPoint>> snkField;

class snkState
{
public:
    snkState() = default;
    virtual ~snkState() = default;

    void ClearBuf();

    virtual void Init(int w, int h) = 0;
    virtual State Update(int key) = 0;

    const snkField& GetGameField();

protected:
    void Construct(int w, int h);
    virtual void Refresh() = 0;
    void CreateItem(const char* text, int size, int row);
    void CreateItem(const chtype* text, int size, int row);

protected:
    snkField mBuf;

    int mW {0};
    int mH {0};
};

#endif /* _SNK_STATE_H_ */
