/**
 * @file      snkConsole.cpp
 * @brief     Contains implementation of base class for console window system
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.1
 * @date      01/04/2022
 * @copyright GNU Public License
 */

#include "snkConsole.h"

#include "snkMenu.h"
#include "snkGame.h"
#include "snkNick.h"
#include "snkRecs.h"

const std::string snkConsole::appName = "Snake";

const int snkConsole::WIN_W = 33;
const int snkConsole::WIN_H = 17;
const int snkConsole::SCR_W = WIN_W - 2;
const int snkConsole::SCR_H = WIN_H - 2;

snkConsole::~snkConsole() {}

bool snkConsole::Init()
{
    /* Stop if another instance of app is already opened */
    if (!mIsContinue)
    {
        return false;
    }

    /* Initializes the terminal in pdcurses mode */
    if (initscr() == nullptr)
    {
        return false;
    }

    /* Checks multicolor mode support */
    if (has_colors() == false)
    {
        return false;
    }

    /* Initializes multicolor mode and creates color pairs */
    start_color();
    init_pair(WHT_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED_BLACK, COLOR_RED,   COLOR_BLACK);
    init_pair(GRN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(BLU_BLACK, COLOR_CYAN,  COLOR_BLACK);

    /* Creates game field */
    mWin = CreateWin(WIN_H, WIN_W, 0, 0);

    /* Creates bar for score and level mark */
    mBar = CreateWin(3, WIN_W, WIN_H, 0);

    /* Makes cursor invisible */
    curs_set(0);

    /* Curses preparations */
    cbreak();
    keypad(mWin, TRUE);
    noecho();

    /* Creates game states */
    mGameStates.resize(static_cast<int>(State::MAXN));
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
    State prevState = mState;
    mState = mGameState->Update(mKey);

    if (mState != prevState)
    {
        /* Refresh game state */
        std::string Nickname = mGameState->GetNickname();

        if ((mGameState = mGameStates[static_cast<int>(mState)].get()))
        {
            mGameState->ClearBuf();
            mGameState->SetNickname(Nickname);
        }
    }

    return mGameState != nullptr;
}

void snkConsole::Render()
{
    if (!mGameState)
    {
        return;
    }

    /* Update game screen */
    const snkField& buf = mGameState->GetGameField();

    for (int i = 0; i < SCR_H; ++i)
    {
        for (int j = 0; j < SCR_W; ++j)
        {
            wattron(mWin, COLOR_PAIR(buf[i][j].mCol));
            mvwaddch(mWin, i + 1, j + 1, buf[i][j].mSym);
            wattroff(mWin, COLOR_PAIR(buf[i][j].mCol));
        }
    }

    wrefresh(mWin);

    /* Update score screen */
    const snkField& bar = mGameState->GetScoreField();

    for (int j = 0; j < SCR_W; ++j)
    {
        wattron(mBar, COLOR_PAIR(bar[0][j].mCol));
        mvwaddch(mBar, 1, j + 1, bar[0][j].mSym);
        wattroff(mBar, COLOR_PAIR(bar[0][j].mCol));
    }

    wrefresh(mBar);
}

void snkConsole::Close()
{
    /* Make cursor visible */
    curs_set(1);

    /* Delete all windows */
    DeleteWin(mBar);
    DeleteWin(mWin);

    /* End pdcurses mode */
    endwin();
}

WINDOW* snkConsole::CreateWin(int h, int w, int y, int x)
{
    WINDOW* wnd = newwin(h, w, y, x);
    box(wnd, 0, 0);
    wrefresh(wnd);

    return wnd;
}

void snkConsole::DeleteWin(WINDOW* wnd)
{
    wborder(wnd, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(wnd);
    delwin(wnd);
}
