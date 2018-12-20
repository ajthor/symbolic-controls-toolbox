// ----------------------------------------------------------------------
// C Wrapper API Function Definitions
//

#include <iostream>
#include <functional>
#include <random>
#include <vector>

extern "C" {

#ifndef C_WRAPPER_RETURN_TYPE
#define C_WRAPPER_RETURN_TYPE int
#endif

#ifndef C_WRAPPER_NO_EXCEPTION
#define C_WRAPPER_NO_EXCEPTION 0
#endif

#ifndef C_WRAPPER_RUNTIME_EXCEPTION
#define C_WRAPPER_RUNTIME_EXCEPTION 1
#endif

#ifndef C_WRAPPER_BEGIN
#define C_WRAPPER_BEGIN try {
#endif

#ifndef C_WRAPPER_END
#define C_WRAPPER_END(Default) \
  } \
  catch(const std::exception &e) { \
    std::cerr << "An error occurred." << '\n'; \
    std::cerr << e.what() << '\n'; \
    return Default; \
  }
#endif

// Code goes here.

} // C
