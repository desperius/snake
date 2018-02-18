/**
 * @file      main.cpp
 * @brief     There is an entry point to start main application.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      14/02/2018
 * @copyright GNU Public License
 */

#include "main.h"

int main()
{
    std::unique_ptr<snkApp> app;

    try
    {
        app = std::unique_ptr<snkApp>(new snkApp());
    }
    catch (...)
    {
        exit(EXIT_FAILURE);
    }

    return app->Run();
}
