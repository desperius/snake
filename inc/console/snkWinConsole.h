/**
 *   @file      snkWinConsole.h
 *   @brief     Contains class for console window system for Windows OS
 *   @author    Alexander Orel (desperius@gmail.com)
 *   @version   1.0
 *   @date      12.09.2016
 *   @copyright GNU Public License
 */

#ifndef _SNK_WIN_CONSOLE_H_
#define _SNK_WIN_CONSOLE_H_

#ifdef __WIN32__

#include "snkConsole.h"
#include "snkMenu.h"
#include "snkGame.h"
#include <windows.h>

class snkWinConsole : public snkConsole
{
public:
   snkWinConsole() = default;
   virtual ~snkWinConsole() = default;

   bool Init() override;
   void Close() override;

   void Event() override;
   bool Loop() override;
   void Render() override;

private:
   WINDOW* CreateWin(int h, int w, int y, int x);
   void DeleteWin(WINDOW* wnd);

private:
   HANDLE mMutex {nullptr};
   WINDOW* mWin;
   WINDOW* mBar;

   int  mKey {0};

   std::shared_ptr<snkState> mGameState;
};

#endif /* __WIN32__ */

#endif /* _SNK_WIN_CONSOLE_H_ */
