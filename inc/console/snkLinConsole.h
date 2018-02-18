/**
 * @file      snkLinConsole.h
 * @brief     Contains class for console window for Linux.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      15/02/2018
 * @copyright GNU Public License
 */

#ifndef _SNK_LIN_CONSOLE_H_
#define _SNK_LIN_CONSOLE_H_

#ifdef __linux__

#include "snkConsole.h"

/**
 * @class snkLinConsole
 * @brief Implements platform specific creation and destroying of Linux console window.
 */
class snkLinConsole : public snkConsole
{
public:
    snkLinConsole();
    virtual ~snkLinConsole();

    snkLinConsole(const snkLinConsole&  that) = delete;
    snkLinConsole(const snkLinConsole&& that) = delete;

    snkLinConsole& operator=(const snkLinConsole&  that) = delete;
    snkLinConsole& operator=(const snkLinConsole&& that) = delete;
private:
    int mSocket = {-1}; //! Descriptor for created endpoint
    int mRC = {1};      //! Return code of bind()
};

#endif /* __linux__ */

#endif /* _SNK_LIN_CONSOLE_H_ */
