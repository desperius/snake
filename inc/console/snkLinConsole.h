/**
 *   @file      snkLinConsole.h
 *   @brief     Contains class for console window system for Linux OS
 *   @author    Alexander Orel (desperius@gmail.com)
 *   @version   1.0
 *   @date      26.10.2016
 *   @copyright GNU Public License
 */
 
 #ifndef _SNK_LIN_CONSOLE_H_
 #define _SNK_LIN_CONSOLE_H_
 
#ifdef __linux__

#include "snkConsole.h"

class snkLinConsole : public snkConsole
{
public:
   snkLinConsole();
   ~snkLinConsole();
   
   bool Init() override;
   void Close() override;
   
private:
   int mSocket {-1};
   int mRC {1};
};

#endif /* __linux__ */
 
#endif /* _SNK_LIN_CONSOLE_H_ */