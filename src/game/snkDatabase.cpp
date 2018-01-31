#include "snkDatabase.h"

#include <stdlib.h>
#include <string>

static int callback(void* data, int argc, char** argv, char** colName)
{
    int* count = reinterpret_cast<int*>(data);

    if (data != nullptr)
    {
        *count = std::atoi(argv[0]);
    }

    for (int i = 0; i < argc; ++i)
    {
        std::string(colName[i]) + " " + std::string(argv[i]);
    }

    return 0;
}

void snkDatabase::Connect()
{
    mError = sqlite3_open("recs.db", &mDB);

    /* Database opened. Creates the table */
    if (SQLITE_OK == mError)
    {
        mQuery = "create table if not exists players (";
        mQuery += "id int primary key not null, ";
        mQuery += "nick text not null, ";
        mQuery += "score int not null);";

        sqlite3_exec(mDB, mQuery.c_str(), callback, nullptr, &mErrMsg);
    }
}

void snkDatabase::Write(std::string nick, int score)
{
    mQuery = "select count(*) from players";
    sqlite3_exec(mDB, mQuery.c_str(), callback, &mCount, &mErrMsg);

    if (mCount < MAX_RECORDS)
    {
        Insert(++mCount, nick, score);
    }
    else
    {
        Update(mCount, nick, score);
    }
}

void snkDatabase::Insert(int id, std::string nick, int score)
{
    /* Inserts record into database */
    mQuery = "insert into players (id, nick, score) values (";
    mQuery += std::to_string(id) + ",";
    mQuery += "'" + nick + "',";
    mQuery += std::to_string(score) + ");";

    sqlite3_exec(mDB, mQuery.c_str(), callback, nullptr, &mErrMsg);
}

void snkDatabase::Update(int id, std::string nick, int score)
{
    mQuery = "select id,score from players where score<=";
    mQuery += std::to_string(score) + " order by score asc";

    sqlite3_stmt* statement = nullptr;

    int rc = sqlite3_prepare_v2(mDB, mQuery.c_str(), -1, &statement, nullptr);
    std::string str_id;

    if (SQLITE_OK == rc)
    {
        while (true)
        {
            rc = sqlite3_step(statement);

            if (SQLITE_ROW == rc)
            {
                str_id = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
                break;
            }

            if (SQLITE_DONE == rc || SQLITE_ERROR == rc)
            {
                break;
            }
        }
    }

    if (!str_id.empty())
    {
        mQuery = "update players set nick='";
        mQuery += nick + "', score=";
        mQuery += std::to_string(score) + " where id=";
        mQuery += str_id;

        rc = sqlite3_prepare_v2(mDB, mQuery.c_str(), -1, &statement, nullptr);

        if (SQLITE_OK == rc)
        {
            sqlite3_step(statement);
            sqlite3_finalize(statement);
        }
    }
}

void snkDatabase::Close()
{
    sqlite3_close(mDB);
}

std::vector<std::string> snkDatabase::GetTable()
{
    std::vector<std::string> recs;

    mQuery = "select nick,score from players order by score desc";

    sqlite3_stmt* statement = nullptr;
    int rc = sqlite3_prepare(mDB, mQuery.c_str(), -1, &statement, 0);
    std::string str_id;

    if (rc == SQLITE_OK)
    {
        int total = sqlite3_column_count(statement);

        while (true)
        {
            rc = sqlite3_step(statement);

            if (rc == SQLITE_ROW)
            {
                for (int i = 0; i < total; ++i)
                {
                    std::string str = reinterpret_cast<const char*>(sqlite3_column_text(statement, i));
                    recs.push_back(str);
                }
            }

            if (rc == SQLITE_DONE || rc == SQLITE_ERROR)
            {
                break;
            }
        }
    }

    return recs;
}
