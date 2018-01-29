#ifndef _SNK_DATABASE_H_
#define _SNK_DATABASE_H_

#include "sqlite3.h"

class snkDatabase
{
public:
    snkDatabase() = default;
    ~snkDatabase() = default;

    void Connect();
    void Write(std::string nick, int score);
    void Close();

    void Print();

private:
    void Insert(int id, std::string nick, int score);
    void Update(int id, std::string nick, int score);

private:
    sqlite3* mDB = {nullptr};
    char* mErrMsg = {nullptr};
    int mError = 0;
};

#endif /* _SNK_DATABASE_H_ */
