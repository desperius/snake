/**
 * @brief Contains implementation of class for work with SQL database
 */

#include "snkDatabase.hpp"

using Statement = std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)>;

bool snkDatabase::Connect()
{
    if (mDatabase)
    {
        return true;
    }

    constexpr char query[] = R"sql(
        CREATE TABLE IF NOT EXISTS players (
            id INT PRIMARY KEY NOT NULL,
            nick TEXT NOT NULL,
            score INT NOT NULL
        )
    )sql";

    sqlite3* raw = nullptr;
    const int rc = sqlite3_open("recs.db", &raw);
    Connection connection(raw, &sqlite3_close_v2);

    if (rc != SQLITE_OK)
    {
        return false;
    }

    if (sqlite3_exec(connection.get(), query, nullptr, nullptr, nullptr) != SQLITE_OK)
    {
        return false;
    }

    mDatabase.swap(connection);
    return true;
}

bool snkDatabase::Write(const std::string &nick, const int score) const
{
    if (!mDatabase)
    {
        return false;
    }

    constexpr char query[] = R"sql(
        INSERT INTO players (id, nick, score)
        SELECT
            CASE
                WHEN COUNT(*) < ?3 THEN COALESCE(MAX(id), 0) + 1
                ELSE (SELECT id FROM players ORDER BY score ASC, id ASC LIMIT 1)
            END,
            ?1,
            ?2
        FROM players
        WHERE 1
        ON CONFLICT(id) DO UPDATE SET
            nick = excluded.nick,
            score = excluded.score
        WHERE excluded.score >= players.score
    )sql";

    sqlite3_stmt* raw = nullptr;
    int rc = sqlite3_prepare_v2(mDatabase.get(), query, -1, &raw, nullptr);
    const Statement statement(raw, &sqlite3_finalize);

    if (rc != SQLITE_OK)
    {
        return false;
    }

    rc = sqlite3_bind_text(statement.get(), 1, nick.c_str(), -1, SQLITE_TRANSIENT);

    if (rc != SQLITE_OK)
    {
        return false;
    }

    rc = sqlite3_bind_int(statement.get(), 2, score);

    if (rc != SQLITE_OK)
    {
        return false;
    }

    rc = sqlite3_bind_int(statement.get(), 3, MAX_RECORDS);

    if (rc != SQLITE_OK)
    {
        return false;
    }

    return sqlite3_step(statement.get()) == SQLITE_DONE;
}

void snkDatabase::Close()
{
    mDatabase.reset();
}

bool snkDatabase::GetTable(std::vector<std::string>& records) const
{
    if (!mDatabase)
    {
        return false;
    }

    constexpr char query[] = "SELECT nick, score FROM players ORDER BY score DESC";

    sqlite3_stmt* raw = nullptr;
    int rc = sqlite3_prepare_v2(mDatabase.get(), query, -1, &raw, nullptr);

    const Statement statement(raw, &sqlite3_finalize);

    if (rc != SQLITE_OK)
    {
        return false;
    }

    std::vector<std::string> results;
    const int columnCount = sqlite3_column_count(statement.get());

    while ((rc = sqlite3_step(statement.get())) == SQLITE_ROW)
    {
        for (int column = 0; column < columnCount; ++column)
        {
            const auto* value = sqlite3_column_text(statement.get(), column);

            if (!value)
            {
                return false;
            }

            results.emplace_back(reinterpret_cast<const char*>(value));
        }
    }

    if (rc != SQLITE_DONE)
    {
        return false;
    }

    records.swap(results);
    return true;
}
