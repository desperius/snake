/**
 * @file      snkRecs.h
 * @brief     Contains implementation of class for display of records table.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.1
 * @date      01/04/2022
 * @copyright GNU Public License
 */

#include "snkRecs.h"

#include <algorithm>

snkRecs::snkRecs(int w, int h) : snkState(w, h)
{
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
    mRecs = mDB.GetTable();

    ClearBuf();

    AddStrToBuf(to_snk_string("RECORDS TABLE"), 0);
    
    snkString txt = to_snk_string(" #  Nickname      Score");
    AddStrToBuf(txt, 2);
    
    int length = txt.length();
    
    txt = snkString(length, ACS_HLINE);
    AddStrToBuf(txt, 3);
    
    for (std::size_t i = 0, j = 1; i < mRecs.size(); ++i, ++j)
    {
        /* Indent for numbers less then ten */
        std::string str = j < 10 ? " " : "";

        /* Add point to number */
        str += std::to_string(j) + ". ";

        /* Add player's nickname */
        str += mRecs[i++];

        /* Align by nickname and fill with spaces */
        int size = length - str.length() - mRecs[i].length();
        str += std::string(size, ' ');

        /* Add score */
        str += mRecs[i];
        AddStrToBuf(to_snk_string(str), 4 + (i / 2));
    }

    AddStrToBar(to_snk_string("Press END key to exit"), 0);
}
