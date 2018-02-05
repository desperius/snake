#ifndef _SNK_DATABASE_H_
#define _SNK_DATABASE_H_

#include <vector>
#include <string>

#include "sqlite3.h"

class snkDatabase
{
public:
    snkDatabase() = default;
    ~snkDatabase() = default;

    void Connect();
    void Write(std::string& nick, int score);
    void Close();

    std::vector<std::string> GetTable();

private:
    void Insert(int id, std::string& nick, int score);
    void Update(int id, std::string& nick, int score);

private:
    static const int8_t MAX_RECORDS = 10;
    std::string mQuery;
    sqlite3* mDB = {nullptr};
    char* mErrMsg = {nullptr};
    int mError = {0};
    int mCount = {0};
};

#endif /* _SNK_DATABASE_H_ */
