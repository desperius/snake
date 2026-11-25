#include "main.hpp"

#include <iostream>

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
