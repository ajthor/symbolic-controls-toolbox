// ----------------------------------------------------------------------
// Matlab Wrapper API Function Definitions
//
// Matlab-specific functions go here.
#ifndef CONTROL_MATLAB_MATLAB_WRAPPER_HPP
#define CONTROL_MATLAB_MATLAB_WRAPPER_HPP

#ifdef __cplusplus
extern "C" {
#endif

int say_hello();


typedef struct StateSpace_C StateSpace_C;

StateSpace_C* statespace_new();
void statespace_free(StateSpace_C* obj);


typedef struct MDP_C MDP_C;

MDP_C* mdp_new();
void mdp_free(MDP_C* obj);

void mdp_set_num_states(MDP_C* obj, int arg);
void mdp_set_num_inputs(MDP_C* obj, int arg);
void mdp_set_gamma(MDP_C* obj, double arg);

int mdp_get_num_states(MDP_C* obj);
int mdp_get_num_inputs(MDP_C* obj);
double mdp_get_gamma(MDP_C* obj);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: CONTROL_MATLAB_MATLAB_WRAPPER_HPP */
