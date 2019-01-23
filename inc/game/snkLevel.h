/**
 * @file      snkLevel.h
 * @brief     Contains class for levels generation and management.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      16/02/2018
 * @copyright GNU Public License
 */

#ifndef _SNK_LEVEL_H_
#define _SNK_LEVEL_H_

/* + food */
/* # wall */

#include <list>
#include "snkState.h"

/**
 * @class snkLevel
 * @brief Implements functionality for levels generation and management.
 */
class snkLevel
{
public:
    snkLevel() = default;
    ~snkLevel() = default;

    snkLevel(const snkLevel&  that) = delete;
    snkLevel(const snkLevel&& that) = delete;

    snkLevel& operator=(const snkLevel&  that) = delete;
    snkLevel& operator=(const snkLevel&& that) = delete;

    /**
     * @brief Initializes resources for levels generation and management.
     * @param w Width of game field.
     * @param h Height of game field.
     * @param[in] food_sym Symbol for display food on the game field.
     * @param[in] wall_sym Symbol for display wall on the game field.
     */
    void Init(int w, int h, chtype food_sym, chtype wall_sym);

    /**
     * @brief Returns list of wall points for the current level.
     * @return List of points.
     */
    std::list<snkPoint> GenWall();

    /**
     * @brief Randomly generates position of new food. Excludes snake body and wall.
     * @param[in] body Current body of the snake.
     * @param[in] wall Current wall on the level.
     * @return Point with random coordinates.
     */
    snkPoint GenFood(const std::list<snkPoint>& body, const std::list<snkPoint>& wall);

    /**
     * @brief Relocates wall on one point in predefined direction.
     * @param[in,out] wall Wall which will be moved.
     * @param currTime Current absolute game time.
     */
    void Move(std::list<snkPoint>& wall, std::chrono::milliseconds currTime);

    /**
     * @brief Returns number of current level.
     * @return Number of current level.
     */
    int GetLevel() const;

    /**
     * @brief Increases the level number.
     */
    void LevelUp();

    /**
     * @brief Increases the sublevel number.
     */
    void SubLeveUp();

    /**
     * @brief Returns state of win condition reached.
     * @return True if win condition reached.
     */
    bool IsWin() const;

private:
    /**
     * @brief Forms horizontal line of wall points.
     * @param[out] wall List where wall points will be saved.
     */
    void hLine(std::list<snkPoint>& wall);

    /**
     * @brief Forms vertical line of wall points.
     * @param[out] wall List where wall points will be saved.
     */
    void vLine(std::list<snkPoint>& wall);

    /**
     * @brief Forms horizontal dashed line of wall points.
     * @param[out] wall List where wall points will be saved.
     */
    void hDash(std::list<snkPoint>& wall);

    /**
     * @brief Forms vertical dashed line of wall points.
     * @param[out] wall List where wall points will be saved.
     */
    void vDash(std::list<snkPoint>& wall);

    /**
     * @brief Forms horizontal line for moving wall.
     * @param[out] wall List where wall points will be saved.
     */
    void hmLine(std::list<snkPoint>& wall);

    /**
     * @brief Forms vertical line for moving wall.
     * @param[out] wall List where wall points will be saved.
     */
    void vmLine(std::list<snkPoint>& wall);

    /**
     * @brief Moves wall horizontally in predefined direction.
     */
    void MoveH();

    /**
     * @brief Moves wall vertically in predefined direction.
     */
    void MoveV();

private:
    static const int WALL_SPEED = 800;   //! Maximal wall speed
    std::chrono::milliseconds mPrevTime; //! Previous time
    std::list<snkPoint> mWallMoveH;      //! Wall which will be moved horizontally
    std::list<snkPoint> mWallMoveV;      //! Wall which will be moved vertically
    int mW = {0};                        //! Width of game field
    int mH = {0};                        //! Height of game field
    int mLevelNum = {0};                 //! Current level number
    int mSubLevel = {0};                 //! Current sublevel number
    chtype mFoodSym;                     //! Symbol corresponding to food
    chtype mWallSym;                     //! Symbol corresponding to wall
    bool mIsMoveLeft = {false};          //! Is wall moving left?
    bool mIsMoveDown = {false};          //! Is wall moving down?
    bool mIsWin = {false};               //! Win condition
    bool mIsStart = {true};              //! Mark for start of the current level
};

#endif /* _SNK_LEVEL_H_ */
