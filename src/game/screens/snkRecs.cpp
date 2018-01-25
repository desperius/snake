#include "snkRecs.h"
#include "snkLog.h"
#include "sqlite3.h"

void snkRecs::Init(int w, int h)
{
    snkState::Construct(w, h);

    sqlite3* db = nullptr;
    int rc = sqlite3_open("recs.db", &db);

    if (rc)
    {
        snkLog::Get().Log(std::string(sqlite3_errmsg(db)));
    }

    sqlite3_close(db);
}

State snkRecs::Update(int key)
{
    State ret = State::RECS;

    switch (key)
    {
        case KEY_END:
        {
            ret = State::MENU;
            break;
        }

        default:
        {
            Refresh();
            break;
        }
    }

    return ret;
}

void snkRecs::Refresh()
{
    ClearBuf();

    std::string str = "Records Table";
    AddStr(str, 0);

    str = "Press END key to exit";
    AddStrToBar(str, 0);
}
