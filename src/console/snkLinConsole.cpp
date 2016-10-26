/**
 *   @file      snkLinConsole.cpp
 *   @brief     Contains implementation of class for console window system for Linux OS
 *   @author    Alexander Orel (desperius@gmail.com)
 *   @version   1.0
 *   @date      26.10.2016
 *   @copyright GNU Public License
 */
 
#ifdef __linux__

#include <netinet/in.h>
#include <unistd.h>
#include "snkLinConsole.h"
#include "log/snkLog.h"

snkLinConsole::snkLinConsole()
{
}

snkLinConsole::~snkLinConsole()
{
   Close();
}

bool snkLinConsole::Init()
{
   if ((mSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
      return false;
   }
   else
   {
      struct sockaddr_in name;
      name.sin_family = AF_INET;
      name.sin_port = htons(7373);
      name.sin_addr.s_addr = htonl(INADDR_ANY);
      mRC = bind(mSocket, reinterpret_cast<struct sockaddr*>(&name), sizeof(name));
   }
   
   return (mSocket != -1 && mRC == 0);
}

void snkLinConsole::Close()
{
   if (mSocket != -1)
   {
      close(mSocket);
   }
}

#endif /* __linux__ */