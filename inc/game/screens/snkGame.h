#ifndef _SNK_GAME_H_
#define _SNK_GAME_H_

#include "snkState.h"
#include "snkSnake.h"
#include <chrono>

class snkGame : public snkState
{
public:
    snkGame() = default;
    virtual ~snkGame() = default;

    void Init(int w, int h) override;
    State Update(int key) override;

private:
    void Refresh() override;

private:
    std::chrono::milliseconds mTime;
    snkSnake mSnake;
    int mScore;
};

#endif /* _SNK_GAME_H_ */
