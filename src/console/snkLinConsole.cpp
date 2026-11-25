/**
 * @brief Contains implementation of class for platform specific console window for Linux
 */

#ifdef __linux__

#include "snkLinConsole.hpp"

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
