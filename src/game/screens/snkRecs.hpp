/**
 * @brief Contains class for display of records table
 */

#pragma once

#include "snkState.hpp"
#include "snkDatabase.hpp"

/**
 * @brief Implements functionality for display of records table
 */
class snkRecs : public snkState
{
public:
    snkRecs(const int w, const int h);
    ~snkRecs() override = default;

    State Update(const int key) override;

protected:
    void Refresh() override;

private:
    snkDatabase mDB;                //! Instance of database of records
    std::vector<std::string> mRecs; //! Vector of records from database
    bool mDatabaseReady = false;
};
