// ----------------------------------------------------------------------
// C Wrapper API Function Definitions
//

#include <symengine/basic.h>
#include <symengine/cwrapper.h>

#include "c_wrapper.hpp"

#include "mdp.hpp"
#include "state_space.hpp"
#include "transfer_function.hpp"

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
    return; \
  } \
  catch (...) { \
    return; \
  }
#endif

// struct RCPBasic_C {
//   SymEngine::RCP<const SymEngine::Basic> m;
// };

struct CRCPBasic {
  SymEngine::RCP<const SymEngine::Basic> m;
};

// ----------------------------------------------------------------------
// StateSpace Function Definitions
//
struct StateSpace_C {
  Controls::StateSpace m;
};

StateSpace_C *statespace_new() {
  return new StateSpace_C;
}

void statespace_free(StateSpace_C *obj) {
  if(!obj) {
    return;
  }
  delete obj;
}

void statespace_states_push_back(StateSpace_C *obj, const basic arg) {
  C_WRAPPER_BEGIN

  obj->m.add_state(arg->m);

  C_WRAPPER_END
}

void statespace_states_get(StateSpace_C *obj, size_t n, basic result) {
  C_WRAPPER_BEGIN

  // TODO: n < obj->m.size()
  result->m = obj->m.get_state(n);

  C_WRAPPER_END
}

void statespace_states_set(StateSpace_C *obj, size_t n, const basic arg) {
  C_WRAPPER_BEGIN

  // TODO: n < obj->m.size()
  obj->m.set_state(n, arg->m);

  C_WRAPPER_END
}

// void statespace_states_erase(StateSpace_C *obj, size_t n) {
//   C_WRAPPER_BEGIN
//
//   C_WRAPPER_END
// }

size_t statespace_states_size(StateSpace_C *obj) {
  return obj->m.get_num_states();
}


// ----------------------------------------------------------------------
// MDP Function Definitions
//
struct MDP_C {
  Controls::MDP m;
};

// struct SparseMatrix_key {
//   sparse_key_t k
// };
// typedef struct SparseMatrix_key SparseMatrix_key;
//
// struct SparseMatrix_C {
//   SparseMatrix<double> m;
// };
// typedef struct SparseMatrix_C SparseMatrix_C;

// ----------------------------------------------------------------------
// TransferFunction Function Definitions
//
struct TransferFunction_C {
  Controls::TransferFunction m;
};

// TransferFunction_C* transferfunction_new() {
//   return new TransferFunction_C;
// }
//
// void transferfunction_free(TransferFunction_C* obj) {
//   if(!obj) {
//     return;
//   }
//   delete obj;
// }

} // C
