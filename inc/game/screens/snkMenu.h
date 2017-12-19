#ifndef _SNK_MENU_H_
#define _SNK_MENU_H_

#include "snkState.h"

class snkMenu : public snkState
{
public:
    snkMenu() = default;
    virtual ~snkMenu() = default;

    void Init(int w, int h) override;
    State Update(int key) override;

private:
    void Refresh() override;

private:
    State mActive {State::GAME};
};

#endif /* _SNK_MENU_H_ */
