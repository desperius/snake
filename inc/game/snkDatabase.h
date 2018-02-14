/**
 * @file      snkDatabase.h
 * @brief     Contains class for work with SQL database.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      16/02/2018
 * @copyright GNU Public License
 */

#ifndef _SNK_DATABASE_H_
#define _SNK_DATABASE_H_

#include <vector>
#include <string>

#ifdef __WIN32__
#include "sqlite3.h"
#endif /* __WIN32__ */

#ifdef __linux__
#include <sqlite3.h>
#endif /* __linux__ */

/**
 * @class snkDatabase
 * @brief Implements functionality for work with SQL database.
 */
class snkDatabase
{
public:
    snkDatabase() = default;
    ~snkDatabase() = default;

    snkDatabase(const snkDatabase&  that) = delete;
    snkDatabase(const snkDatabase&& that) = delete;

    snkDatabase& operator=(const snkDatabase&  that) = delete;
    snkDatabase& operator=(const snkDatabase&& that) = delete;

    /**
     * @brief Opens database connection.
     */
    void Connect();

    /**
     * @brief Adds record to the database.
     * @param[in] nick Player's nickname.
     * @param[in] score Player's score.
     */
    void Write(std::string& nick, int score);

    /**
     * @brief Closes database connection.
     */
    void Close();

    /**
     * @brief Gets all records from the database.
     * @return Vector of records.
     */
    std::vector<std::string> GetTable();

private:
    /**
     * @brief Creates new record in the database.
     * @param[in] id New record ID.
     * @param[in] nick Nickname which writes in new record.
     * @param[in] score Score which writes in new record.
     */
    void Insert(int id, std::string& nick, int score);

    /**
     * @brief Updates an existing record in the database.
     * @param[in] id ID of the record which should be updated.
     * @param[in] nick Nickname which writes in record.
     * @param[in] score Score which writes in record.
     */
    void Update(int id, std::string& nick, int score);

private:
    static const int8_t MAX_RECORDS = 10; //! Maximal number of records in database
    std::string mQuery;                   //! Query to the database
    sqlite3* mDB = {nullptr};             //! Pointer to opened database
    char* mErrMsg = {nullptr};            //! Error massage
    int mError = {0};                     //! Error code
    int mCount = {0};                     //! Number of records in database at the moment
};

#endif /* _SNK_DATABASE_H_ */
