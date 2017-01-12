#include "main.h"

#include <string>

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
