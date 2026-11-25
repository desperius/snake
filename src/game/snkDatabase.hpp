/**
 * @brief Contains class for work with SQL database.
 */

#pragma once

#include <memory>
#include <vector>
#include <string>

#ifdef _WIN32
#include "sqlite3.h"
#endif /* _WIN32 */

#ifdef __linux__
#include <sqlite3.h>
#endif /* __linux__ */

/**
 * @brief Implements functionality for work with SQL database
 */
class snkDatabase
{
public:
    snkDatabase() = default;
    ~snkDatabase() = default;

    snkDatabase(const snkDatabase&  that) = delete;
    snkDatabase(snkDatabase&& that) = delete;

    snkDatabase& operator=(const snkDatabase&  that) = delete;
    snkDatabase& operator=(snkDatabase&& that) = delete;

    /**
     * @brief Opens database connection
     * @return true if connection was opened successfully, false otherwise
     */
    bool Connect();

    /**
     * @brief Adds record to the database
     * @param[in] nick Player's nickname
     * @param[in] score Player's score
     * @return true if record was added successfully, false otherwise
     */
    bool Write(const std::string &nick, const int score) const;

    /**
     * @brief Closes database connection
     */
    void Close();

    /**
     * @brief Gets all records from the database
     * @param[in] records Previous records
     * @return true if records were retrieved successfully, false otherwise
     */
    bool GetTable(std::vector<std::string>& records) const;

private:
    static constexpr int8_t MAX_RECORDS = 10; //! Maximal number of records in database

    using Connection = std::unique_ptr<sqlite3, decltype(&sqlite3_close_v2)>;
    Connection mDatabase = { nullptr, &sqlite3_close_v2 }; //! Pointer to opened database
};
