#ifndef _SNK_STATE_H_
#define _SNK_STATE_H_

#include "pdcurses.h"

#include <string>
#include <vector>

enum class State : int
{
    MENU = 1,
    GAME = MENU + 2,
    RECS = GAME + 2,
    EXIT = RECS + 2,
    NICK = EXIT + 2
};

enum Color
{
    WHT_BLACK = 1,
    RED_BLACK = 2,
    GRN_BLACK = 3,
    BLU_BLACK = 4
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
    const snkField& GetScoreField();

    std::string GetNickname();
    void SetNickname(const std::string& nickname);

protected:
    void Construct(int w, int h);
    virtual void Refresh() = 0;
    void AddStr(const std::string& text, int row, int col = 0);
    void AddTxt(const chtype* text, int size, int row, int col = 0);

    void AddStrToBar(const std::string& text, int row, int col = 0);
    void AddTxtToBar(const chtype* text, int size, int row, int col = 0);

protected:
    snkField mBuf;
    snkField mBar;

    int mW = {0};
    int mH = {0};

    std::string mNickname;
};

#endif /* _SNK_STATE_H_ */
