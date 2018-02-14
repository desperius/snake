/**
 * @file      snkRecs.h
 * @brief     Contains implementation of class for display of records table.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      16/02/2018
 * @copyright GNU Public License
 */

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
        /* Indent for numbers less then ten */
        str = j < 10 ? " " : "";

        /* Add point to number */
        str += std::to_string(j) + ". ";

        /* Add player's nickname */
        str += mRecs[i++];

        /* Align by nickname and fill with spaces */
        int size = length - str.length() - mRecs[i].length();
        str += std::string(size, ' ');

        /* Add score */
        str += mRecs[i];
        AddStr(str, 4 + (i / 2));
    }

    str = "Press END key to exit";
    AddStrToBar(str, 0);
}
