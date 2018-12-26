/**
 * @file      snkConsole.cpp
 * @brief     Contains implementation of base class for console window system
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      15/02/2018
 * @copyright GNU Public License
 */

#include "snkConsole.h"

#include "snkMenu.h"
#include "snkGame.h"
#include "snkNick.h"
#include "snkRecs.h"

const std::string snkConsole::appName = "Snake";

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
    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(GRN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(BLU_BLACK, COLOR_CYAN, COLOR_BLACK);

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

    /* Creates pointer for game state */
    mGameState = std::make_shared<snkMenu>();
    mGameState->Init(SCR_W, SCR_H);

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
    bool ret = true;

    State prevState = mState;
    mState = mGameState->Update(mKey);

    if (mState != prevState)
    {
        /* Refresh game state */
        if (State::MENU == mState)
        {
            mGameState = std::make_shared<snkMenu>();
            mGameState->Init(SCR_W, SCR_H);
        }
        else if (State::NICK == mState)
        {
            mGameState = std::make_shared<snkNick>();
            mGameState->Init(SCR_W, SCR_H);
        }
        else if (State::GAME == mState)
        {
            std::string nickname = mGameState->GetNickname();
            mGameState = std::make_shared<snkGame>();
            mGameState->Init(SCR_W, SCR_H);
            mGameState->SetNickname(nickname);
        }
        else if (State::RECS == mState)
        {
            mGameState = std::make_shared<snkRecs>();
            mGameState->Init(SCR_W, SCR_H);
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}

void snkConsole::Render()
{
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
