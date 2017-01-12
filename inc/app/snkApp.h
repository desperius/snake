#ifndef _SNK_APP_H_
#define _SNK_APP_H_

#ifdef __WIN32__
#include "snkWinConsole.h"
#endif /* __WIN32__ */

#ifdef __linux__
#include "snkLinConsole.h"
#endif /* __linux__ */

class snkApp
{
public:
   snkApp();
   ~snkApp() = default;

public:
   int  Run();

private:
   bool Init();
   void Event();
   void Loop();
   void Render();
   void Close();

private:
   bool mRunning {true};
   std::unique_ptr<snkConsole> mConsole;
};

#endif /* _SNK_APP_H_ */
