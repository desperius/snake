/**
 * @file      main.cpp
 * @brief     There is an entry point to start main application.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.1
 * @date      01/04/2022
 * @copyright GNU Public License
 */

#include "main.h"

int main()
{
    std::unique_ptr<snkApp> app;

    try
    {
        app = std::make_unique<snkApp>();
    }
    catch (...)
    {
        exit(EXIT_FAILURE);
    }

    return app->Run();
}
