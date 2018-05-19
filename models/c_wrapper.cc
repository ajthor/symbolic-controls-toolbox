// ----------------------------------------------------------------------
// C Wrapper API Function Definitions
//

#include "c_wrapper.hpp"

#include "state_space.hpp"
#include "transfer_function.hpp"

using Controls::StateSpace;
using Controls::TransferFunction;

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
#define C_WRAPPER_END \
    return C_WRAPPER_NO_EXCEPTION; \
    catch (...) { \
      return C_WRAPPER_RUNTIME_EXCEPTION; \
    } \
  }
#endif

// ----------------------------------------------------------------------
// StateSpace Function Definitions
//
struct StateSpace_C {
  Controls::StateSpace m;
};

StateSpace_C* symss_new() {
  return new StateSpace_C;
}

void symss_free(StateSpace_C* obj) {
  delete obj;
}

// ----------------------------------------------------------------------
// TransferFunction Function Definitions
//
struct TransferFunction_C {
  Controls::TransferFunction m;
};

TransferFunction_C* symtf_new() {
  return new TransferFunction_C;
}

void symtf_free(TransferFunction_C* obj) {
  delete obj;
}

} // C
