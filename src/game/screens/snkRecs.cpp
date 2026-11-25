/**
 * @brief Contains implementation of class for display of records table
 */

#include "snkRecs.hpp"

#include <algorithm>

snkRecs::snkRecs(const int w, const int h) : snkState(w, h)
{
    mDatabaseReady = mDB.Connect();
    snkRecs::Refresh();
}

State snkRecs::Update(const int key)
{
    auto ret = State::RECS;

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
    const bool loaded = mDatabaseReady && mDB.GetTable(mRecs);

    ClearBuf();

    AddStrToBuf(to_snk_string("RECORDS TABLE"), 0);
    
    snkString txt = to_snk_string(" #  Nickname      Score");
    AddStrToBuf(txt, 2);
    
    const size_t length = txt.length();
    
    txt = snkString(length, ACS_HLINE);
    AddStrToBuf(txt, 3);
    
    for (size_t i = 0, j = 1; i < mRecs.size(); ++i, ++j)
    {
        // Indent for numbers less than ten
        std::string str = j < 10 ? " " : "";

        // Add point to number
        str += std::to_string(j) + ". ";

        // Add player's nickname
        str += mRecs[i++];

        // Align by nickname and fill with spaces
        const size_t size = length - str.length() - mRecs[i].length();
        str += std::string(size, ' ');

        // Add score
        str += mRecs[i];
        AddStrToBuf(to_snk_string(str), static_cast<int>(4 + (i / 2)));
    }

    if (!loaded)
    {
        AddStrToBuf(to_snk_string("Couldn't load records"), 0);
    }

    AddStrToBar(to_snk_string("Press END key to exit"), 0);
}
