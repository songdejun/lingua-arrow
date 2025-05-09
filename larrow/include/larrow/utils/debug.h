#pragma once

#ifdef NDEBUG

#define LOG_FUNC() ((void)0)

#else

#include <iostream>
#define LOG_FUNC()                                                             \
  std::cout << "[DEBUG] CALL:" << __FUNCTION__ << "(" << __FILE__ << ":"       \
            << __LINE__ << ")\n"

#endif
