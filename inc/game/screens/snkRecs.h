/**
 * @file      snkRecs.h
 * @brief     Contains class for display of records table.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      16/02/2018
 * @copyright GNU Public License
 */

#ifndef _SNK_RECS_H_
#define _SNK_RECS_H_

#include "snkState.h"
#include "snkDatabase.h"

/**
 * @class snkRecs
 * @brief Implements functionality for display of records table.
 */
class snkRecs : public snkState
{
public:
    snkRecs() = default;
    ~snkRecs() = default;

    /**
     * @brief Initializes resources for current game state.
     * @param[in] w Width of game field.
     * @param[in] h Height of game field.
     */
    void Init(int w, int h) override;

    /**
     * @brief Updates actual game data based on input.
     * @param[in] key Code of pressed key.
     * @return Current game state.
     */
    State Update(int key) override;

private:
    /**
     * @brief Refresh values of game field and status bar.
     */
    void Refresh() override;

private:
    snkDatabase mDB;                //! Instance of database of records
    std::vector<std::string> mRecs; //! Vector of records from database
};

#endif /* _SNK_RECS_H_ */
