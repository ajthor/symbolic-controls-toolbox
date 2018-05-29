// ----------------------------------------------------------------------
// Matlab Wrapper API Function Definitions
//

#include <cstdlib>
#include <cstring>
#include <symengine/basic.h>
#include <symengine/cwrapper.h>
#include <vector>
// For C. C Matrix API.
#include <matrix.h>
// For C++. MATLAB Data API.
// #include <MatlabDataArray.hpp>

#include "matlab_wrapper.hpp"

#include "libctrl/c_wrapper.hpp"

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

// void statespace_set_states(StateSpace_C* obj, matlab::data::Array arg) {
//   int i = 0;
//   for (auto e : arg) {
//     obj->m.set_state(i++, SymEngine::symbol(std::string(e)));
//   }
// }
//
// matlab::data::Array statespace_get_states(StateSpace_C* obj) {
//   using namespace matlab::data;
//
//   std::vector<SymEngine::RCP<const SymEngine::Basic>> states = obj->m.get_states();
//
//   size_t sz = states.size();
//
//   ArrayFactory factory;
//   TypedArray<String> ret = factory.createArray({1, sz});
//
//   int i = 0;
//   for (auto elem : states) {
//     ret[i++] = elem;
//   }
//
//   return ret;
// }

void statespace_set_state(StateSpace_C* obj, const int idx, const char* arg) {
  obj->m.set_state(idx - 1, SymEngine::symbol(std::string(arg)));
}

// TODO: If vector is empty, return empty string.
char** statespace_get_states(StateSpace_C* obj) {
  using namespace SymEngine;
  std::vector<RCP<const Basic>> states = obj->m.get_states();

  char* ret[states.size()];
  int i = 0;
  for(auto e : states) {
    std::string str = e->__str__();
    auto cc = new char[str.length() + 1];
    std::strcpy(ret[i++], str.c_str());
  }

  return ret;

}

char* statespace_get_state(StateSpace_C* obj, const int idx) {
  using namespace SymEngine;
  std::vector<RCP<const Basic>> states = obj->m.get_states();

  std::string str = states.at(idx)->__str__();
  auto cc = new char[str.length() + 1];
  std::strcpy(cc, str.c_str());

  return cc;
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
