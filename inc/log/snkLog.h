#ifndef _SNK_LOG_H_
#define _SNK_LOG_H_

#include <iostream>

#ifdef  DEBUG
#define LOG(x) do { std::cout << x << std::endl; } while(0)
#else
#define LOG(x)
#endif

#endif /* _SNK_LOG_H_ */