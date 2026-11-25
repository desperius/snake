/**
 * @brief Contains class for console window for Linux
 */

#pragma once


#ifdef __linux__

#include "snkConsole.h"

/**
 * @brief Implements platform specific creation and destroying of Linux console window.
 */
class snkLinConsole : public snkConsole
{
public:
    snkLinConsole();
    virtual ~snkLinConsole();

    snkLinConsole(const snkLinConsole&  that) = delete;
    snkLinConsole(snkLinConsole&& that) = delete;

    snkLinConsole& operator=(const snkLinConsole&  that) = delete;
    snkLinConsole& operator=(snkLinConsole&& that) = delete;
private:
    int mSocket = -1; //! Descriptor for created endpoint
    int mRC = 1;      //! Return code of bind()
};

#endif /* __linux__ */
