#ifndef _SNK_NICK_H_
#define _SNK_NICK_H_

#include "snkState.h"

class snkNick : public snkState
{
public:
    snkNick() = default;
    virtual ~snkNick() = default;

    void Init(int w, int h) override;
    State Update(int key) override;

private:
    void Refresh() override;
    std::vector<chtype> GenLine(chtype l, chtype m, chtype r);

private:
    static const int MAX_NICK_SIZE = 10;
};

#endif /* _SNK_NICK_H_ */
