#ifndef _SNK_RECS_H_
#define _SNK_RECS_H_

#include "snkState.h"
#include "snkDatabase.h"

class snkRecs : public snkState
{
public:
    snkRecs() = default;
    ~snkRecs() = default;

    void Init(int w, int h) override;
    State Update(int key) override;

private:
    void Refresh() override;

private:
    snkDatabase mDB;
    std::vector<std::string> mRecs;
};

#endif /* _SNK_RECS_H_ */
