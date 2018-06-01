// ----------------------------------------------------------------------
// Matlab Wrapper API Function Definitions
//

// API Rules
// - Only use C standard types that convert to Matlab basic types. Convert to
//   more advanced types in Matlab or C++.
// - Do not return pointers. Modify pointers in the parameters. Only return
//   simple types if the values are scalar. This is because Matlab
//   automatically adds a return variable to interpreted function calls to a
//   shared library.

#ifndef CONTROL_MATLAB_MATLAB_WRAPPER_HPP
#define CONTROL_MATLAB_MATLAB_WRAPPER_HPP

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// State Space wrapper functions.
//
typedef struct StateSpace_C StateSpace_C;

StateSpace_C* ml_statespace_new();
void ml_statespace_free(StateSpace_C *obj);

void ml_statespace_states_push_back(StateSpace_C *obj, const char* arg);
void ml_statespace_states_get(StateSpace_C *obj, char **result);
void ml_statespace_states_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_states_size(StateSpace_C *obj);

void ml_statespace_inputs_push_back(StateSpace_C *obj, const char* arg);
void ml_statespace_inputs_get(StateSpace_C *obj, char **result);
void ml_statespace_inputs_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_inputs_size(StateSpace_C *obj);

void ml_statespace_f_push_back(StateSpace_C *obj, const char* arg);
void ml_statespace_f_get(StateSpace_C *obj, char **result);
void ml_statespace_f_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_f_size(StateSpace_C *obj);

void ml_statespace_g_push_back(StateSpace_C *obj, const char* arg);
void ml_statespace_g_get(StateSpace_C *obj, char **result);
void ml_statespace_g_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_g_size(StateSpace_C *obj);

void ml_statespace_A_get(StateSpace_C *obj, char **result);
void ml_statespace_B_get(StateSpace_C *obj, char **result);
void ml_statespace_C_get(StateSpace_C *obj, char **result);
void ml_statespace_D_get(StateSpace_C *obj, char **result);

// ----------------------------------------------------------------------
// MDP wrapper functions.
//
// typedef struct MDP_C MDP_C;
//
// MDP_C* mdp_new();
// void mdp_free(MDP_C* obj);
//
// void mdp_set_num_states(MDP_C* obj, int arg);
// void mdp_set_num_inputs(MDP_C* obj, int arg);
// void mdp_set_gamma(MDP_C* obj, double arg);
//
// int mdp_get_num_states(MDP_C* obj);
// int mdp_get_num_inputs(MDP_C* obj);
// double mdp_get_gamma(MDP_C* obj);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: CONTROL_MATLAB_MATLAB_WRAPPER_HPP */
