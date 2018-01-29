#include <stdlib.h>
#include <string>

#include "snkDatabase.h"
#include "snkLog.h"

int callback(void* data, int argc, char** argv, char** colName)
{
    int* count = reinterpret_cast<int*>(data);

    if (data != nullptr)
    {
        *count = std::atoi(argv[0]);
    }

    for (int i = 0; i < argc; ++i)
    {
        std::string str = std::string(colName[i]) + " " + std::string(argv[i]);
        snkLog::Get().Log(str);
    }

    return 0;
}

void snkDatabase::Connect()
{
    mError = sqlite3_open("recs.db", &mDB);

    if (SQLITE_OK == mError)
    {
        std::string sql = "CREATE TABLE IF NOT EXISTS PLAYERS ( \
                          ID INT PRIMARY KEY NOT NULL, \
                          NICK TEXT NOT NULL, \
                          SCORE INT NOT NULL);";

        sqlite3_exec(mDB, sql.c_str(), callback, nullptr, &mErrMsg);
    }
}

void snkDatabase::Write(std::string nick, int score)
{
    int count = 0;
    std::string sql = "SELECT COUNT(*) FROM PLAYERS";
    sqlite3_exec(mDB, sql.c_str(), callback, &count, &mErrMsg);

    if (count < 10)
    {
        Insert(++count, nick, score);
    }
    else
    {
        Update(count, nick, score);
    }
}

void snkDatabase::Insert(int id, std::string nick, int score)
{
    std::string sql = "INSERT INTO PLAYERS (ID, NICK, SCORE) VALUES (";
    sql += std::to_string(id) + ",";
    sql += "'" + nick + "',";
    sql += std::to_string(score) + ");";

    sqlite3_exec(mDB, sql.c_str(), callback, nullptr, &mErrMsg);
}

void snkDatabase::Update(int id, std::string nick, int score)
{
    sqlite3_stmt* statement = nullptr;
    std::string sql = "select id,score from players where score<=";
    sql += std::to_string(score) + " order by score asc";

    int rc = sqlite3_prepare_v2(mDB, sql.c_str(), -1, &statement, nullptr);
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

    sql = "update players set nick='";
    sql += nick + "', score=";
    sql += std::to_string(score) + " where id=";
    sql += str_id;

    rc = sqlite3_prepare_v2(mDB, sql.c_str(), -1, &statement, nullptr);

    if (SQLITE_OK == rc)
    {
        sqlite3_step(statement);
        sqlite3_finalize(statement);
    }
}

void snkDatabase::Close()
{
    sqlite3_close(mDB);
}

void snkDatabase::Print()
{
    sqlite3_stmt* statement = nullptr;
    std::string sql = "select nick,score from players order by score desc";

    int rc = sqlite3_prepare(mDB, sql.c_str(), -1, &statement, 0);
    std::string str_id;

    if (rc == SQLITE_OK)
    {
        int total = sqlite3_column_count(statement);
        int row = 0;

        while (true)
        {
            rc = sqlite3_step(statement);

            if (rc == SQLITE_ROW)
            {
                row += 1;

                for (int i = 0; i < total; ++i)
                {
                    std::string str = reinterpret_cast<const char*>(sqlite3_column_text(statement, i));
                    snkLog::Get().Log(str);
                }
            }

            if (rc == SQLITE_DONE || rc == SQLITE_ERROR)
            {
                break;
            }
        }
    }
}
