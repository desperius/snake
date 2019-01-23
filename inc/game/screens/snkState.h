/**
 * @file      snkState.h
 * @brief     Contains base class for game state.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      10/01/2019
 * @copyright GNU Public License
 */

#ifndef _SNK_STATE_H_
#define _SNK_STATE_H_

#include <string>
#include <vector>
#include <chrono>

#ifdef __WIN32__
#include "pdcurses.h"
#endif /* __WIN32__ */

#ifdef __linux__
#include <ncurses.h>
#endif /* __linux__ */

#ifdef __WIN32__
#include "pdcurses.h"
#endif /* __WIN32__ */

#ifdef __linux__
#include <ncurses.h>
#endif /* __linux__ */

/**
 * @brief The enumeration to represent game states.
 */
enum class State : int
{
    MENU = 1,        //! Start menu
    GAME = MENU + 2, //! Game itself
    RECS = GAME + 2, //! Records table
    EXIT = RECS + 2, //! Exit
    NICK = EXIT + 2  //! Nick enter screen
};

/**
 * @brief The enumeration of colors for output
 */
enum Color
{
    WHT_BLACK = 1, //! White on black background
    RED_BLACK = 2, //! Red on black background
    GRN_BLACK = 3, //! Green on black background
    BLU_BLACK = 4  //! Blue on black background
};

/**
 * @struct snkPoint
 * @brief  A structure to represent points of the game field.
 */
struct snkPoint
{
    explicit snkPoint(int x = 0, int y = 0, chtype sym = ' ', Color col = WHT_BLACK)
        : mX(x)
        , mY(y)
        , mSym(sym)
        , mCol(col)
    {}

    ~snkPoint() = default;

    int mX;      //! X-coordinate on the game field
    int mY;      //! Y-coordinate on the game field
    chtype mSym; //! Character in the point
    Color  mCol; //! Color of the character
};

typedef std::vector<std::vector<snkPoint>> snkField;
typedef std::basic_string<chtype> snkString;

snkString to_snk_string(std::string txt);

/**
 * @class snkState
 * @brief Implements base functionality of game state.
 */
class snkState
{
public:
    snkState() = default;
    virtual ~snkState() = default;

    snkState(const snkState&  that) = delete;
    snkState(const snkState&& that) = delete;

    snkState& operator=(const snkState&  that) = delete;
    snkState& operator=(const snkState&& that) = delete;

    /**
     * @brief Clears character buffers of game field and status bar.
     */
    void ClearBuf();

    /**
     * @brief Initializes resources for current game state.
     * @param[in] w Width of game field.
     * @param[in] h Height of game field.
     */
    virtual void Init(int w, int h) = 0;

    /**
     * @brief Updates actual game data based on input.
     * @param[in] key Code of pressed key.
     * @return Current game state.
     */
    virtual State Update(int key) = 0;

    /**
     * @brief Returns array of game field points.
     * @return Reference to two dimensional vector.
     */
    const snkField& GetGameField() const;

    /**
     * @brief Returns array of status bar points.
     * @return Reference to two dimensional vector.
     */
    const snkField& GetScoreField() const;

    /**
     * @brief Returns player's nickname.
     * @return String with a nickname.
     */
    std::string GetNickname() const;

    /**
     * @brief Sets player's nickname.
     * @param[in] nickname String with a nickname.
     */
    void SetNickname(const std::string& nickname);

protected:
    /**
     * @brief Creates common resources for all game states.
     * @param[in] w Width of game field.
     * @param[in] h Height of game field.
     */
    void Construct(int w, int h);

    /**
     * @brief Refresh values of game field and status bar.
     */
    virtual void Refresh() = 0;

    /**
     * @brief Adds STL string to game field.
     * @param[in] text Text which need to be printed.
     * @param[in] row Row position where text need to be placed.
     * @param[in] col Column position where text need to be placed.
     */
    void AddStrToBuf(const snkString& text, int row, int col = 0);

    /**
     * @brief Adds STL string to status bar.
     * @param[in] text Text which need to be printed.
     * @param[in] row Row position where text need to be placed.
     * @param[in] col Column position where text need to be placed.
     */
    void AddStrToBar(const snkString& text, int row, int col = 0);

    /**
     * @brief Creates border of frame.
     * @param[in] len Frame length.
     * @param[in] l Symbol for left side of frame.
     * @param[in] m Symbol for middle side of frame.
     * @param[in] r Symbol for right side of frame.
     * @return Final snkString of frame.
     */
    static snkString GenFrameLine(int len, chtype l, chtype m, chtype r);

private:
    /**
     * @brief Adds null-terminated string to the field.
     * @param[in] buf Buffer in which string should be added.
     * @param[in] text Text which need to be printed.
     * @param[in] size Length of the input string.
     * @param[in] row Row position where text need to be placed.
     * @param[in] col Column position where text need to be placed.
     */
    void AddTxt(snkField& buf, const chtype* text, int size, int row, int col = 0);

protected:
    /*
    * @brief Lines and corners to build a rectangle frame
    */
    static chtype ULC;
    static chtype URC;
    static chtype HLN;
    static chtype VLN;
    static chtype LLC;
    static chtype LRC;

    static const int MAX_FRAME_SIZE = 9; //! Maximal wide of frame

    snkField mBuf;         //! Two dimensional vector for game field points
    snkField mBar;         //! Two dimensional vector for status bar points

    int mW = {0};          //! Width of game field
    int mH = {0};          //! Height of game field

    std::string mNickname; //! Player's nickname

};

#endif /* _SNK_STATE_H_ */
