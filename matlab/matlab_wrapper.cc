// ----------------------------------------------------------------------
// Matlab Wrapper API Function Definitions
//
// Most of the function wrappers in the Matlab wrappers are designed to implement Matlab's matrix syntax. All variables in Matlab are defined as vectors and matrices, meaning we need to implement a lot of for loops and ** pointers in order to make the C wrappers work with Matlab.

#include <cstdlib>
#include <cstring>
#include <vector>

#include <symengine/basic.h>
#include <symengine/cwrapper.h>
#include <symengine/symbol.h>

// For C. C Matrix API.
#include <mex.h>
#include <matrix.h>
// For C++. MATLAB Data API.
// #include <MatlabDataArray.hpp>

#include "matlab_wrapper.hpp"

#include "libctrl/c_wrapper.hpp"

// ----------------------------------------------------------------------
// Convert SymEngine to Matlab Symbolic and vice-versa.
//
// mxArray* se2sym(SymEngine::RCP<const SymEngine::Basic> arg) {
//   mxArray* matlab_sym;
//
//   return matlab_sym;
// }
//
// SymEngine::RCP<const SymEngine::Basic> sym2se(mxArray* arg) {
//   SymEngine::RCP<const SymEngine::Basic> symengine_sym;
//
//   return symengine_sym;
// }

extern "C" {

// struct RCPBasic_C {
//   SymEngine::RCP<const SymEngine::Basic> m;
// };
struct CRCPBasic {
  SymEngine::RCP<const SymEngine::Basic> m;
};

// ----------------------------------------------------------------------
// State Space wrapper functions.
//
StateSpace_C* ml_statespace_new() {
  return statespace_new();
}

void ml_statespace_free(StateSpace_C *obj) {
  statespace_free(obj);
}

void ml_statespace_states_push_back(StateSpace_C *obj, const char* arg) {
  auto s = basic_new_heap();
  basic_const_set(s, arg);

  statespace_states_push_back(obj, s);

  basic_free_heap(s);
}

void ml_statespace_states_get(StateSpace_C *obj, char **result) {
  size_t sz = statespace_states_size(obj);
  int i = 0;
  for(i = 0; i < sz; i++) {
    auto s = basic_new_heap();
    statespace_states_get(obj, i, s);

    std::string str = s->m->__str__();

    result[i] = new char[str.length() + 1];
    std::strcpy(result[i], str.c_str());

    basic_free_heap(s);
  }
}

// void ml_statespace_states_get(StateSpace_C *obj, char** result) {
//   size_t sz = statespace_states_size(obj);
//   int i = 0;
//   for(i = 0; i < sz; i++) {
//     RCPBasic_C *s;
//     statespace_states_get(obj, i, s);
//
//     std::string str = s->m->__str__();
//
//     // mexPrintf("str.c_str: %s\n", str.c_str());
//
//     // auto res = result[i];
//     // std::strcpy(res, str.c_str());
//     // result[i] = &str[0u];
//
//     result[i] = new char[str.length() + 1];
//     // result[i] = alloca(str.size() + 1);
//     std::strcpy(result[i], str.c_str());
//
//     // mexPrintf("cstr %d: %s\n", i, cstr);
//     // mexPrintf("cstr %d: %d\n", i, cstr);
//
//     // std::strcpy(result[i], cc);
//     // std::strcpy(result[i], str.c_str());
//     // result[i] = cc;
//
//     // result[i] = str.c_str();
//     // result[i] = "else";
//     // mexPrintf("result %d: %s\n", i, result[i]);
//   }
//
//   // return result;
// }

void ml_statespace_states_set(StateSpace_C *obj, int len, const char** arg) {
  size_t sz = statespace_states_size(obj);
  int i = 0;
  for(i = 0; i < len; i++) {
    auto s = basic_new_heap();
    basic_const_set(s, arg[i]);

    if(i >= sz) {
      statespace_states_push_back(obj, s);
    } else {
      statespace_states_set(obj, i, s);
    }

    basic_free_heap(s);
  }
}

int ml_statespace_states_size(StateSpace_C *obj) {
  return statespace_states_size(obj);
}

// void statespace_set_states(StateSpace_C *obj, matlab::data::Array arg) {
//   int i = 0;
//   for (auto e : arg) {
//     obj->m.set_state(i++, SymEngine::symbol(std::string(e)));
//   }
// }
//
// matlab::data::Array statespace_get_states(StateSpace_C *obj) {
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

// void statespace_set_state(StateSpace_C *obj, const int idx, const char* arg) {
//   obj->m.set_state(idx - 1, SymEngine::symbol(std::string(arg)));
// }
//
// // TODO: If vector is empty, return empty string.
// char** statespace_get_states(StateSpace_C *obj) {
//   using namespace SymEngine;
//   std::vector<RCP<const Basic>> states = obj->m.get_states();
//
//   char* ret[states.size()];
//   int i = 0;
//   for(auto e : states) {
//     std::string str = e->__str__();
//     auto cc = new char[str.length() + 1];
//     std::strcpy(ret[i++], str.c_str());
//   }
//
//   return ret;
//
// }
//
// char* statespace_get_state(StateSpace_C *obj, const int idx) {
//   using namespace SymEngine;
//   std::vector<RCP<const Basic>> states = obj->m.get_states();
//
//   std::string str = states.at(idx)->__str__();
//   auto cc = new char[str.length() + 1];
//   std::strcpy(cc, str.c_str());
//
//   return cc;
// }

// ----------------------------------------------------------------------
// MDP wrapper functions.
//
// struct MDP_C {
//   Controls::MDP m;
// };
//
// MDP_C* mdp_new() {
//   return new MDP_C;
// }
//
// void mdp_free(MDP_C* obj) {
//   delete obj;
// }
//
// void mdp_set_num_states(MDP_C* obj, int arg) {
//   obj->m.set_num_states(arg);
// }
//
// void mdp_set_num_inputs(MDP_C* obj, int arg) {
//   obj->m.set_num_inputs(arg);
// }
//
// void mdp_set_gamma(MDP_C* obj, double arg) {
//   obj->m.set_gamma(arg);
// }
//
// int mdp_get_num_states(MDP_C* obj) {
//   return obj->m.get_num_states();
// }
//
// int mdp_get_num_inputs(MDP_C* obj) {
//   return obj->m.get_num_inputs();
// }
//
// double mdp_get_gamma(MDP_C* obj) {
//   return obj->m.get_gamma();
// }


} // C
