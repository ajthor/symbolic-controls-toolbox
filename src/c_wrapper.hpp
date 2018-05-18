// ---------------------------------------------------------------------------
// C Wrapper API Interface
//

#ifndef C_WRAPPER_HPP
#define C_WRAPPER_HPP

#include "models/state_space.hpp"
#include "models/transfer_function.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------
// C Wrapper for StateSpace Interface
//
typedef struct StateSpace_C StateSpace_C;

StateSpace_C* statespace_new();
void statespace_free(StateSpace_C* obj);

// void statespace_set_states(StateSpace_C* obj);

// ---------------------------------------------------------------------------
// C Wrapper for TransferFunction Interface
//
typedef struct TransferFunction_C TransferFunction_C;

TransferFunction_C* transferfunction_new();
void transferfunction_free(TransferFunction_C* obj);


#ifdef __cplusplus
}
#endif

#endif /* end of include guard: C_WRAPPER_HPP */
