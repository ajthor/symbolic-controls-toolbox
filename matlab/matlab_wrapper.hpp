// ----------------------------------------------------------------------
// Matlab Wrapper API Function Definitions
//

// API Rules
// - Only use C standard types that convert to Matlab basic types. Convert to
//   more advanced types in Matlab or C++.
// - Do not return pointers. Modify pointers in the parameters. Only return
//   simple types if the values are scalar. This is because Matlab
//   automatically adds a return variable to interpreted function calls to a
//   shared library if the parameter is changed.
// - Implement Matlab array-handling only. Do not re-invent functionality or
//   create new functionality, unless it is unique and specific to Matlab.

#ifndef CONTROL_MATLAB_MATLAB_WRAPPER_HPP
#define CONTROL_MATLAB_MATLAB_WRAPPER_HPP

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Linear algebra wrapper functions.
//
void ml_la_hessenberg(int len, char **A, char **result);
void ml_la_schur(int len, char **A, char **U, char **T);
void ml_la_eigenvalues(int len, char **A, char **l, char **v);

// ----------------------------------------------------------------------
// State Space wrapper functions.
//
typedef struct StateSpace_C StateSpace_C;

StateSpace_C* ml_statespace_new();

void ml_statespace_free(StateSpace_C *obj);

void ml_statespace_states_get(StateSpace_C *obj, char **result);
void ml_statespace_states_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_states_size(StateSpace_C *obj);

void ml_statespace_inputs_get(StateSpace_C *obj, char **result);
void ml_statespace_inputs_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_inputs_size(StateSpace_C *obj);

void ml_statespace_f_get(StateSpace_C *obj, char **result);
void ml_statespace_f_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_f_size(StateSpace_C *obj);

void ml_statespace_g_get(StateSpace_C *obj, char **result);
void ml_statespace_g_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_g_size(StateSpace_C *obj);

void ml_statespace_A_get(StateSpace_C *obj, char **result);
void ml_statespace_B_get(StateSpace_C *obj, char **result);
void ml_statespace_C_get(StateSpace_C *obj, char **result);
void ml_statespace_D_get(StateSpace_C *obj, char **result);

void ml_statespace_subs(StateSpace_C *obj,
                        int len,
                        const char **a,
                        const char **b);

void ml_statespace_linearize(StateSpace_C *obj);

void ml_statespace_ctrb(StateSpace_C *obj, char **result);
void ml_statespace_obsv(StateSpace_C *obj, char **result);

// ----------------------------------------------------------------------
// MDP wrapper functions.
//
typedef struct MDP_C MDP_C;

MDP_C* ml_mdp_new();
void ml_mdp_free(MDP_C* obj);

int ml_mdp_get_num_states(MDP_C* obj);
void ml_mdp_set_num_states(MDP_C* obj, int arg);

int ml_mdp_get_num_inputs(MDP_C* obj);
void ml_mdp_set_num_inputs(MDP_C* obj, int arg);

void ml_mdp_probabilities_set(MDP_C *obj,
                              size_t u,
                              size_t x,
                              size_t xp,
                              const double arg);
double ml_mdp_probabilities_get(MDP_C *obj,
                                size_t u,
                                size_t x,
                                size_t xp);
void ml_mdp_rewards_set(MDP_C *obj,
                        size_t u,
                        size_t x,
                        size_t xp,
                        const double arg);
double ml_mdp_rewards_get(MDP_C *obj,
                          size_t u,
                          size_t x,
                          size_t xp);

double ml_mdp_get_gamma(MDP_C* obj);
void ml_mdp_set_gamma(MDP_C* obj, double arg);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: CONTROL_MATLAB_MATLAB_WRAPPER_HPP */
