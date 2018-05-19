// ---------------------------------------------------------------------------
// C Wrapper API Interface
//

#ifndef MODELS_C_WRAPPER_HPP
#define MODELS_C_WRAPPER_HPP

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------
// C Wrapper for StateSpace Interface
//
typedef struct StateSpace_C StateSpace_C;

StateSpace_C* symss_new();
void symss_free(StateSpace_C* obj);

// void symss_set_states(StateSpace_C* obj);

// ---------------------------------------------------------------------------
// C Wrapper for TransferFunction Interface
//
typedef struct TransferFunction_C TransferFunction_C;

TransferFunction_C* symtf_new();
void symtf_free(TransferFunction_C* obj);


#ifdef __cplusplus
}
#endif

#endif /* end of include guard: MODELS_C_WRAPPER_HPP */
