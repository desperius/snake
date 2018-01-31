#include "snkRecs.h"

#include <algorithm>

void snkRecs::Init(int w, int h)
{
    snkState::Construct(w, h);

    mDB.Connect();
    mRecs = mDB.GetTable();
}

State snkRecs::Update(int key)
{
    State ret = State::RECS;

    switch (key)
    {
        case KEY_END:
        {
            mDB.Close();
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

    std::string str = "RECORDS TABLE";
    AddStr(str, 0);
    str = " #  Nickname      Score";
    int length = str.length();
    AddStr(str, 2);
    std::vector<chtype> txt(length, ACS_HLINE);
    AddTxt(txt.data(), txt.size(), 3);

    for (std::size_t i = 0, j = 1; i < mRecs.size(); ++i, ++j)
    {
        if (j < 10)
        {
            str = " ";
        }
        else
        {
            str = "";
        }

        str += std::to_string(j) + ". ";
        str += mRecs[i++];
        int size = length - str.length() - mRecs[i].length();
        str += std::string(size, ' ');
        str += mRecs[i];
        AddStr(str, 4 + (i / 2));
    }

    str = "Press END key to exit";
    AddStrToBar(str, 0);
}
