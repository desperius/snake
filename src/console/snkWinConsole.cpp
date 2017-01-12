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

#define STR(str) #str

bool snkWinConsole::Init()
{
   // Try to open the mutex
   mMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, appName.c_str());

   if (!mMutex)
   {
      // The mutex does not exist. This is the first instance so create the mutex
      mMutex = CreateMutex(NULL, FALSE, appName.c_str());
   }
   else
   {
      // Bring existing window to the front
      SetForegroundWindow(FindWindow(0, appName.c_str()));

      // The mutex exist so return
      return false;
   }

   SetConsoleTitle(appName.c_str());

   /* Initialize the terminal in pdcurses mode */
   if (nullptr == initscr())
   {
      return false;
   }

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

   mBuf = std::vector<std::vector<char>>(SCR_H + 1, std::vector<char>(SCR_W + 1));

   /* Initialize object for menu state */
   mMenu.Init(mBuf, SCR_W, SCR_H);

   /* Initialize object for game state */
   mGame.Init(mBuf, SCR_W, SCR_H);

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

   if (State::MENU == mState)
   {
      mState = mMenu.Update(mKey);
   }
   else if (State::START == mState)
   {
      mState = mGame.Update(mKey);
   }
   else if (State::ABOUT == mState)
   {
      ret = true;
   }
   else
   {
      ret = false;
   }

   return ret;
}

void snkWinConsole::Render()
{
   for (int i = 0; i < SCR_H; ++i)
   {
      mvwprintw(mWin, i + 1, 1, "%s", mBuf[i].data());
   }

   wrefresh(mWin);
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
