/**
 *   @file      snkConsole.h
 *   @brief     Contains base class for console window system
 *   @author    Alexander Orel (desperius@gmail.com)
 *   @version   1.0
 *   @date      08.09.2016
 *   @copyright GNU Public License
 */

#ifndef _SNK_CONSOLE_H_
#define _SNK_CONSOLE_H_

#include <string>

class snkConsole
{
public:
   snkConsole();
   virtual ~snkConsole();

   virtual bool Init() = 0;
   virtual void Close() = 0;

protected:
   static const std::string appName;
};

#endif /* _SNK_CONSOLE_H_ */
