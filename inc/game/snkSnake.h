/**
 * @file      snkState.h
 * @brief     Contains class for snake management.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      15/02/2018
 * @copyright GNU Public License
 */

#ifndef _SNK_SNAKE_H_
#define _SNK_SNAKE_H_

#include <list>

#include "snkState.h"

/**
 * @brief The enumeration to represent snake movement direction.
 */
enum class Dir : short
{
    UP = 1,
    LF = 2,
    DN = 3,
    RT = 4
};

/**
 * @class snkSnake
 * @brief Implements functionality for snake management.
 */
class snkSnake
{
public:
    snkSnake()  = default;
    ~snkSnake() = default;

    snkSnake(const snkSnake&  that) = delete;
    snkSnake(const snkSnake&& that) = delete;

    snkSnake& operator=(const snkSnake&  that) = delete;
    snkSnake& operator=(const snkSnake&& that) = delete;

    /**
     * @brief Initializes resources needed for snake management.
     * @param[in] w Width of game field.
     * @param[in] h Height of game field.
     * @param[in] sym Symbol for displaying of snake body.
     */
    void Init(int w, int h, chtype sym);

    /**
     * @brief Moves snake body in direction corresponding to player's input. Checks collision with food and wall.
     * @param[in] food Chunk of food at the current level.
     * @param[in] wall Wall position at the current level.
     * @param[in] currTime Current absolute game time.
     */
    void Move(const snkPoint& food, const std::list<snkPoint>& wall, std::chrono::milliseconds currTime);

    /**
     * @brief Sets new move direction.
     * @param[in] dir Enumeration for new move direction.
     */
    void SetDir(Dir dir);

    /**
     * @brief Gets current snake moving speed.
     * @return Value of snake speed.
     */
    int GetSpeed() const;

    /**
     * @brief Sets new speed for snake moving.
     * @param[in] speed New value of snake speed.
     */
    void SetSpeed(int speed);

    /**
     * @brief Gets list of points which represents snake body.
     * @return List of points with head at the front.
     */
    std::list<snkPoint> GetBody() const;

    /**
     * @brief Checks game over condition.
     * @return True if it is game over (i.e. snake hited the wall).
     */
    bool IsGameOver() const;

    /**
     * @brief Gets food eaten condition.
     * @return True if food was eaten.
     */
    bool GetIsFed() const;

    /**
     * @brief Sets food eaten condition.
     * @param[in] isFed Food eaten condition.
     */
    void SetIsFed(bool isFed);

    /**
     * @brief Resets all snake properties.
     */
    void Reset();

    /**
     * @brief Resets only snake moving speed.
     */
    void ResetSpeed();

private:
    static const int INIT_SPEED = 500;   //! Snake starting speed
    std::chrono::milliseconds mPrevTime; //! Previous time
    std::list<snkPoint> mBody;           //! Points which represents snake body
    int mW = {0};                        //! Width of game field
    int mH = {0};                        //! Height of game field
    chtype mSym = {'@'};                 //! Initial symbol for snake body
    Dir mDir = {Dir::UP};                //! Initial snake moving direction
    int mSpeed = {INIT_SPEED};           //! Current snake speed. Range [500; 50]
    bool mGameOver = {false};            //! Game over state
    bool mIsFed = {false};               //! Food eaten state
};

#endif /* _SNK_SNAKE_H_ */
