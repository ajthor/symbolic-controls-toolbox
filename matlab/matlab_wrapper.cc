// ----------------------------------------------------------------------
// Matlab Wrapper API Function Definitions
//

#include <symengine/basic.h>

#include "matlab_wrapper.hpp"

#include "libctrl/state_space.hpp"
#include "libctrl/mdp.hpp"

// ----------------------------------------------------------------------
// Convert SymEngine to Matlab Symbolic and vice-versa.
//
mxArray* se2sym(SymEngine::RCP<const SymEngine::Basic> arg) {
  mxArray* matlab_sym;

  return matlab_sym;
}

SymEngine::RCP<const SymEngine::Basic> sym2se(mxArray* arg) {
  SymEngine::RCP<const SymEngine::Basic> symengine_sym;

  return symengine_sym;
}

extern "C" {

// ----------------------------------------------------------------------
// State Space wrapper functions.
//
struct StateSpace_C {
  Controls::StateSpace m;
};

StateSpace_C* statespace_new() {
  return new StateSpace_C;
}

void statespace_free(StateSpace_C* obj) {
  delete obj;
}

// ----------------------------------------------------------------------
// MDP wrapper functions.
//
struct MDP_C {
  Controls::MDP m;
};

MDP_C* mdp_new() {
  return new MDP_C;
}

void mdp_free(MDP_C* obj) {
  delete obj;
}

void mdp_set_num_states(MDP_C* obj, int arg) {
  obj->m.set_num_states(arg);
}

void mdp_set_num_inputs(MDP_C* obj, int arg) {
  obj->m.set_num_inputs(arg);
}

void mdp_set_gamma(MDP_C* obj, double arg) {
  obj->m.set_gamma(arg);
}

int mdp_get_num_states(MDP_C* obj) {
  return obj->m.get_num_states();
}

int mdp_get_num_inputs(MDP_C* obj) {
  return obj->m.get_num_inputs();
}

double mdp_get_gamma(MDP_C* obj) {
  return obj->m.get_gamma();
}


} // C
