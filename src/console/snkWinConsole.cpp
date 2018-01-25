/**
 *   @file      snkWinConsole.cpp
 *   @brief     Contains implementation of class for console window system for Windows OS
 *   @author    Alexander Orel (desperius@gmail.com)
 *   @version   1.0
 *   @date      12.09.2016
 *   @copyright GNU Public License
 */

#ifdef __WIN32__

#include "snkWinConsole.h"
#include "snkMenu.h"
#include "snkGame.h"
#include "snkNick.h"
#include "snkRecs.h"

bool snkWinConsole::Init()
{
    /* Try to open the mutex */
    mMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, appName.c_str());

    if (!mMutex)
    {
        /* The mutex does not exist. This is the first instance so create the mutex */
        mMutex = CreateMutex(NULL, FALSE, appName.c_str());
    }
    else
    {
        /* Bring existing window to the front */
        SetForegroundWindow(FindWindow(0, appName.c_str()));

        /* The mutex exist so return */
        return false;
    }

    SetConsoleTitle(appName.c_str());

    /* Initialize the terminal in pdcurses mode */
    if (initscr() == nullptr)
    {
        return false;
    }

    if (has_colors() == false)
    {
        return false;
    }

    /* Init color mode and make color pairs */
    start_color();
    init_pair(WHT_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(GRN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(BLU_BLACK, COLOR_CYAN, COLOR_BLACK);

    /* Create game field */
    mWin = CreateWin(WIN_H, WIN_W, 0, 0);

    /* Create bar for score and level mark */
    mBar = CreateWin(3, WIN_W, WIN_H, 0);

    /* Make cursor invisible */
    curs_set(0);

    /* Curses preparations */
    cbreak();
    keypad(mWin, TRUE);
    noecho();

    /* Create pointer for game state */
    mGameState = std::make_shared<snkMenu>();
    mGameState->Init(SCR_W, SCR_H);

    return true;
}

void snkWinConsole::Close()
{
    /* Make cursor visible */
    curs_set(1);

    /* Delete all windows */
    DeleteWin(mBar);
    DeleteWin(mWin);

    /* End pdcurses mode */
    endwin();

    /* Close Windows mutex */
    ReleaseMutex(mMutex);
}

void snkWinConsole::Event()
{
    /* Do not wait for input */
    wtimeout(mWin, 0);

    mKey = wgetch(mWin);
}

bool snkWinConsole::Loop()
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

void snkWinConsole::Render()
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

WINDOW* snkWinConsole::CreateWin(int h, int w, int y, int x)
{
    WINDOW* wnd = newwin(h, w, y, x);
    box(wnd, 0, 0);
    wrefresh(wnd);

    return wnd;
}

void snkWinConsole::DeleteWin(WINDOW* wnd)
{
    wborder(wnd, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(wnd);
    delwin(wnd);
}

#endif /* __WIN32__ */
