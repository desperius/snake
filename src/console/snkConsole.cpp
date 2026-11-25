/**
 * @brief Contains implementation of base class for console window system
 */

#include "snkConsole.hpp"

#include "snkWinConsole.hpp"
#include "snkMenu.hpp"
#include "snkGame.hpp"
#include "snkNick.hpp"
#include "snkRecs.hpp"

const std::string snkConsole::appName = "Snake";

const int snkConsole::WIN_W = 33;
const int snkConsole::WIN_H = 17;
const int snkConsole::SCR_W = WIN_W - 2;
const int snkConsole::SCR_H = WIN_H - 2;

std::unique_ptr<snkConsole> snkConsole::Create()
{
#ifdef _WIN32
    return std::make_unique<snkWinConsole>();
#elif __linux__
    return std::make_unique<snkLinConsole>();
#endif
}

bool snkConsole::Init()
{
    // Stop if another instance of app is already opened
    if (!mIsUnique)
    {
        return false;
    }

    // Platform specific initialization of the terminal in PDCurses mode
    if (!InitScr())
    {
        return false;
    }

    // Checks multicolor mode support
    if (!has_colors() || start_color() == ERR)
    {
        Close();
        return false;
    }

    // Initializes multicolor mode and creates color pairs
    start_color();
    init_pair(WHT_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED_BLACK, COLOR_RED,   COLOR_BLACK);
    init_pair(GRN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(BLU_BLACK, COLOR_CYAN,  COLOR_BLACK);

    // Creates game field
    mWin = CreateWin(WIN_H, WIN_W, 0, 0);

    if (!mWin)
    {
        Close();
        return false;
    }

    // Creates bar for score and level mark
    mBar = CreateWin(3, WIN_W, WIN_H, 0);

    if (!mBar)
    {
        Close();
        return false;
    }

    // Makes cursor invisible
    curs_set(0);

    // Curses preparations
    cbreak();
    keypad(mWin, TRUE);
    noecho();

    // Creates game states
    mGameStates.resize(static_cast<int>(State::COUNT));
    mGameStates[static_cast<int>(State::MENU)] = std::make_unique<snkMenu>(SCR_W, SCR_H);
    mGameStates[static_cast<int>(State::GAME)] = std::make_unique<snkGame>(SCR_W, SCR_H);
    mGameStates[static_cast<int>(State::RECS)] = std::make_unique<snkRecs>(SCR_W, SCR_H);
    mGameStates[static_cast<int>(State::EXIT)] = nullptr;
    mGameStates[static_cast<int>(State::NICK)] = std::make_unique<snkNick>(SCR_W, SCR_H);

    mGameState = mGameStates[static_cast<int>(State::MENU)].get();

    return true;
}

void snkConsole::Event()
{
    /* Do not wait for input */
    wtimeout(mWin, 0);

    mKey = wgetch(mWin);
}

bool snkConsole::Loop()
{
    const State prevState = mState;
    mState = mGameState->Update(mKey);

    if (mState != prevState)
    {
        // Refresh game state
        const std::string Nickname = mGameState->GetNickname();

        if ((mGameState = mGameStates[static_cast<int>(mState)].get()))
        {
            mGameState->ClearBuf();
            mGameState->SetNickname(Nickname);
        }
    }

    return mGameState != nullptr;
}

void snkConsole::Render() const
{
    if (!mGameState)
    {
        return;
    }

    // Update game screen
    const snkField& buf = mGameState->GetGameField();

    for (int y = 0; y < SCR_H; ++y)
    {
        for (int x = 0; x < SCR_W; ++x)
        {
            wattron(mWin, COLOR_PAIR(buf[y][x].mCol));
            mvwaddch(mWin, y + 1, x + 1, buf[y][x].mSym);
            wattroff(mWin, COLOR_PAIR(buf[y][x].mCol));
        }
    }

    wrefresh(mWin);

    // Update score screen
    const snkField& bar = mGameState->GetScoreField();

    for (int x = 0; x < SCR_W; ++x)
    {
        wattron(mBar, COLOR_PAIR(bar[0][x].mCol));
        mvwaddch(mBar, 1, x + 1, bar[0][x].mSym);
        wattroff(mBar, COLOR_PAIR(bar[0][x].mCol));
    }

    wrefresh(mBar);
}

void snkConsole::Close()
{
    // Delete all windows
    DeleteWin(mBar);
    mBar = nullptr;
    DeleteWin(mWin);
    mWin = nullptr;

    // End pdcurses mode
    endwin();
}

WINDOW* snkConsole::CreateWin(const int h, const int w, const int y, const int x)
{
    WINDOW* wnd = newwin(h, w, y, x);

    if (!wnd)
    {
        return nullptr;
    }

    box(wnd, 0, 0);
    wrefresh(wnd);

    return wnd;
}

void snkConsole::DeleteWin(WINDOW* wnd)
{
    if (!wnd)
    {
        return;
    }

    wborder(wnd, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(wnd);
    delwin(wnd);
}
