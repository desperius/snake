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

#include "snkState.h"

#include <memory>

class snkConsole
{
public:
    snkConsole() = default;
    virtual ~snkConsole() = default;

    snkConsole(const snkConsole& that) = delete;
    snkConsole(const snkConsole&& that) = delete;
    snkConsole& operator= (const snkConsole& that) = delete;
    snkConsole& operator= (const snkConsole&& that) = delete;

    virtual bool Init() = 0;
    virtual void Close() = 0;
    virtual void Event() = 0;
    virtual bool Loop() = 0;
    virtual void Render() = 0;

protected:
    static const std::string appName;
    static const int WIN_W = {33};
    static const int WIN_H = {17};
    static const int SCR_W = {WIN_W - 2};
    static const int SCR_H = {WIN_H - 2};
    State mState {State::MENU};
};

#endif /* _SNK_CONSOLE_H_ */
