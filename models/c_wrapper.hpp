// ---------------------------------------------------------------------------
// C Wrapper API Interface
//
// The interface provided in this file is the basis for all other language
// bindings to the library. Other language bindings should import this header
// or provide function declarations which implement the same functionality.

#ifndef MODELS_C_WRAPPER_HPP
#define MODELS_C_WRAPPER_HPP

#include "ctrl_export.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RCPBasic_C RCPBasic_C;

// ---------------------------------------------------------------------------
// C Wrapper for StateSpace Interface
//
typedef struct StateSpace_C StateSpace_C;

CTRL_EXPORT StateSpace_C* statespace_new();
CTRL_EXPORT void statespace_free(StateSpace_C* obj);

CTRL_EXPORT void statespace_states_push_back(StateSpace_C* obj, const RCPBasic_C* arg);
CTRL_EXPORT void statespace_states_get(StateSpace_C* obj, size_t n, RCPBasic_C* result);
CTRL_EXPORT void statespace_states_set(StateSpace_C* obj, size_t n, const RCPBasic_C* arg);
CTRL_EXPORT void statespace_states_erase(StateSpace_C* obj, size_t n);
CTRL_EXPORT size_t statespace_states_size(StateSpace_C* obj);

CTRL_EXPORT void statespace_inputs_push_back(StateSpace_C* obj, const basic arg);
CTRL_EXPORT void statespace_inputs_get(StateSpace_C* obj, size_t n, basic result);
CTRL_EXPORT void statespace_inputs_set(StateSpace_C* obj, size_t n, const basic arg);
CTRL_EXPORT void statespace_inputs_erase(StateSpace_C* obj, size_t n);
CTRL_EXPORT size_t statespace_inputs_size(StateSpace_C* obj);

CTRL_EXPORT void statespace_f_push_back(StateSpace_C* obj, const basic arg);
CTRL_EXPORT void statespace_f_get(StateSpace_C* obj, size_t n, basic result);
CTRL_EXPORT void statespace_f_set(StateSpace_C* obj, size_t n, const basic arg);
CTRL_EXPORT void statespace_f_erase(StateSpace_C* obj, size_t n);
CTRL_EXPORT size_t statespace_f_size(StateSpace_C* obj);

CTRL_EXPORT void statespace_g_push_back(StateSpace_C* obj, const basic arg);
CTRL_EXPORT void statespace_g_get(StateSpace_C* obj, size_t n, basic result);
CTRL_EXPORT void statespace_g_set(StateSpace_C* obj, size_t n, const basic arg);
CTRL_EXPORT void statespace_g_erase(StateSpace_C* obj, size_t n);
CTRL_EXPORT size_t statespace_g_size(StateSpace_C* obj);

// ---------------------------------------------------------------------------
// C Wrapper for MDP Interface
//
typedef struct MDP_C MDP_C;

CTRL_EXPORT MDP_C* mdp_new();
CTRL_EXPORT void mdp_free(MDP_C* obj);

CTRL_EXPORT size_t mdp_num_states_get(MDP_C* obj);
CTRL_EXPORT void mdp_num_states_set(MDP_C* obj, size_t n);

CTRL_EXPORT size_t mdp_num_inputs_get(MDP_C* obj);
CTRL_EXPORT void mdp_num_inputs_set(MDP_C* obj, size_t n);

CTRL_EXPORT void mdp_probabilities_get(MDP_C* obj,
                                       size_t x,
                                       size_t xp,
                                       size_t u,
                                       double result);

CTRL_EXPORT void mdp_probabilities_set(MDP_C* obj,
                                       size_t x,
                                       size_t xp,
                                       size_t u,
                                       const double arg);

CTRL_EXPORT void mdp_probabilities_erase(MDP_C* obj, size_t n);

CTRL_EXPORT size_t mdp_probabilities_cols(MDP_C* obj);
CTRL_EXPORT size_t mdp_probabilities_rows(MDP_C* obj);

// CTRL_EXPORT void mdp_probabilities_add_matrix(MDP_C* obj, SparseMatrix_C* a);
// CTRL_EXPORT void mdp_probabilities_mul_matrix(MDP_C* obj, SparseMatrix_C* a);

CTRL_EXPORT void mdp_probabilities_add_scalar(MDP_C* obj, double a);
CTRL_EXPORT void mdp_probabilities_mul_scalar(MDP_C* obj, double a);

CTRL_EXPORT void mdp_rewards_get(MDP_C* obj,
                                 size_t x,
                                 size_t xp,
                                 size_t u,
                                 double result);

CTRL_EXPORT void mdp_rewards_set(MDP_C* obj,
                                 size_t x,
                                 size_t xp,
                                 size_t u,
                                 const double arg);

CTRL_EXPORT void mdp_rewards_erase(MDP_C* obj, size_t n);

CTRL_EXPORT double mdp_gamma_get(MDP_C* obj);
CTRL_EXPORT void mdp_gamma_set(MDP_C* obj, const double n);

// ---------------------------------------------------------------------------
// C Wrapper for TransferFunction Interface
//
typedef struct TransferFunction_C TransferFunction_C;

CTRL_EXPORT TransferFunction_C* transferfunction_new();
CTRL_EXPORT void transferfunction_free(TransferFunction_C* obj);


#ifdef __cplusplus
}
#endif

#endif /* end of include guard: MODELS_C_WRAPPER_HPP */
