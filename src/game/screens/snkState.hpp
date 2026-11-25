/**
 * @brief Contains base class for game state
 */

#pragma once

#include <string>
#include <vector>

#include "curses.h"

/**
 * @brief The enumeration to represent game states
 */
enum class State : int
{
    MENU = 0, //! Start menu
    GAME,     //! Game itself
    RECS,     //! Records table
    EXIT,     //! Exit
    NICK,     //! Nick enter screen
    COUNT     //! Maximal number
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
 * @brief A structure to represent points of the game field
 */
struct snkPoint
{
    explicit snkPoint(const int x = 0, const int y = 0, const chtype sym = ' ', const Color col = WHT_BLACK)
        : mX(x)
        , mY(y)
        , mSym(sym)
        , mCol(col)
    {}

    int mX;      //! X-coordinate on the game field
    int mY;      //! Y-coordinate on the game field
    chtype mSym; //! Character in the point
    Color  mCol; //! Color of the character
};

typedef std::vector<std::vector<snkPoint>> snkField;
typedef std::basic_string<chtype> snkString;

snkString to_snk_string(std::string txt);

/**
 * @brief Implements base functionality of game state
 */
class snkState
{
public:
    /**
     * @brief Class constructor
     * @param[in] w Width of game field
     * @param[in] h Height of game field
     */
    snkState(const int w, const int h);
    virtual ~snkState() = default;

    snkState(const snkState&  that) = delete;
    snkState(snkState&& that) = delete;

    snkState& operator=(const snkState&  that) = delete;
    snkState& operator=(snkState&& that) = delete;

    /**
     * @brief Clears character buffers of game field and status bar
     */
    void ClearBuf();

    /**
     * @brief Updates actual game data based on input
     * @param[in] key Code of pressed key
     * @return Current game state
     */
    virtual State Update(const int key) = 0;

    /**
     * @brief Returns array of game field points
     * @return Reference to two-dimensional vector
     */
    const snkField& GetGameField() const;

    /**
     * @brief Returns array of status bar points
     * @return Reference to two-dimensional vector
     */
    const snkField& GetScoreField() const;

    /**
     * @brief Returns player's nickname
     * @return String with a nickname
     */
    std::string GetNickname() const;

    /**
     * @brief Sets player's nickname
     * @param[in] nickname String with a nickname
     */
    void SetNickname(const std::string& nickname);

protected:
    /**
     * @brief Refresh values of game field and status bar
     */
    virtual void Refresh() = 0;

    /**
     * @brief Adds string to game field
     * @param[in] text Text which need to be printed
     * @param[in] row Row position where text need to be placed
     * @param[in] col Column position where text need to be placed
     */
    void AddStrToBuf(const snkString& text, const int row, const int col = 0);

    /**
     * @brief Adds string to status bar
     * @param[in] text Text which need to be printed
     * @param[in] row Row position where text need to be placed
     * @param[in] col Column position where text need to be placed
     */
    void AddStrToBar(const snkString& text, const int row, const int col = 0);

    /**
     * @brief Creates border of frame
     * @param[in] len Frame length
     * @param[in] l Symbol for left side of frame
     * @param[in] m Symbol for middle side of frame
     * @param[in] r Symbol for right side of frame
     * @return Final snkString of frame
     */
    static snkString GenFrameLine(const int len, const chtype l, const chtype m, const chtype r);

private:
    /**
     * @brief Adds null-terminated string to the field
     * @param[in] buf Buffer in which string should be added
     * @param[in] text Text which need to be printed
     * @param[in] size Length of the input string
     * @param[in] row Row position where text need to be placed
     * @param[in] col Column position where text need to be placed
     */
    void AddTxt(snkField &buf, const chtype *text, const size_t size, const int row, const int col = 0) const;

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

    static constexpr int MAX_FRAME_SIZE = 9; //! Maximal wide of frame

    snkField mBuf; //! Two-dimensional vector for game field points
    snkField mBar; //! Two-dimensional vector for status bar points

    int mW = 0; //! Width of game field
    int mH = 0; //! Height of game field

    std::string mNickname; //! Player's nickname

};
