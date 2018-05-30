// ----------------------------------------------------------------------
// Matlab Wrapper API Function Definitions
//

#ifndef CONTROL_MATLAB_MATLAB_WRAPPER_HPP
#define CONTROL_MATLAB_MATLAB_WRAPPER_HPP

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RCPBasic_C RCPBasic_C;

// ----------------------------------------------------------------------
// State Space wrapper functions.
//
typedef struct StateSpace_C StateSpace_C;

StateSpace_C* ml_statespace_new();
void ml_statespace_free(StateSpace_C* obj);

void ml_statespace_states_push_back(StateSpace_C* obj, const char* arg);
char** ml_statespace_states_get(StateSpace_C* obj);
void ml_statespace_states_set(StateSpace_C* obj, int len, const char** arg);
int ml_statespace_states_size(StateSpace_C* obj);
// void statespace_set_states(StateSpace_C* obj, const mxArray* arg);
// char** statespace_get_states(StateSpace_C* obj);
// char* statespace_get_state(StateSpace_C* obj, const int idx);

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
