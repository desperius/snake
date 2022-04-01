/**
 * @file      snkLinConsole.cpp
 * @brief     Contains implementation of class for platform specific console window for Linux
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      15/02/2018
 * @copyright GNU Public License
 */

#ifdef __linux__

#include "snkLinConsole.h"

#include <netinet/in.h>
#include <unistd.h>

snkLinConsole::snkLinConsole()
{
    if ((mSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        mIsContinue = false;
    }
    else
    {
        struct sockaddr_in name;
        name.sin_family = AF_INET;
        name.sin_port = htons(7373);
        name.sin_addr.s_addr = htonl(INADDR_ANY);
        mRC = bind(mSocket, reinterpret_cast<struct sockaddr*>(&name), sizeof(name));
    }

    mIsContinue = (mSocket != -1) && (mRC == 0);
}

snkLinConsole::~snkLinConsole()
{
    if (mSocket != -1)
    {
        close(mSocket);
    }
}

#endif /* __linux__ */
