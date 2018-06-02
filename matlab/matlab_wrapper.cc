// ----------------------------------------------------------------------
// Matlab Wrapper API Function Definitions
//
// Most of the function wrappers in the Matlab wrappers are designed to
// implement Matlab's matrix syntax. All variables in Matlab are defined as
// vectors and matrices, meaning we need to implement a lot of for loops and **
// pointers in order to make the C wrappers work with Matlab.

#include <cstdlib>
#include <cstring>
#include <vector>

#include <symengine/basic.h>
#include <symengine/matrix.h>
#include <symengine/cwrapper.h>

// For C. C Matrix API.
#include <mex.h>
#include <matrix.h>
// For C++. MATLAB Data API.
// #include <MatlabDataArray.hpp>

#include "matlab_wrapper.hpp"

#include "libctrl/c_wrapper.hpp"

// Re-define here from SymEngine API.
struct CRCPBasic {
  SymEngine::RCP<const SymEngine::Basic> m;
};
struct CVecBasic {
    SymEngine::vec_basic m;
};
struct CDenseMatrix {
    SymEngine::DenseMatrix m;
};

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

// ----------------------------------------------------------------------
// State Space wrapper functions.
//
StateSpace_C* ml_statespace_new() {
  return statespace_new();
}

void ml_statespace_free(StateSpace_C *obj) {
  statespace_free(obj);
}

void ml_statespace_states_get(StateSpace_C *obj, char **result) {
  size_t sz = statespace_states_size(obj);
  int i = 0;
  for(i = 0; i < sz; i++) {
    auto s = basic_new_heap();
    statespace_states_get(obj, i, s);

    std::string str = s->m->__str__();
    // TODO: Convert str here to Matlab Symbolic format.

    result[i] = new char[str.length() + 1];
    std::strcpy(result[i], str.c_str());

    basic_free_heap(s);
  }
}
void ml_statespace_states_set(StateSpace_C *obj, int len, const char** arg) {
  size_t sz = statespace_states_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert arg[i] here to SymEngine format. Pass the formatted string.
    basic_parse(s, arg[i]);

    if(i >= sz) {
      statespace_states_push_back(obj, s);
    } else {
      statespace_states_set(obj, i, s);
    }
  }
  basic_free_heap(s);
}
int ml_statespace_states_size(StateSpace_C *obj) {
  return statespace_states_size(obj);
}

void ml_statespace_inputs_get(StateSpace_C *obj, char **result) {
  size_t sz = statespace_inputs_size(obj);
  int i = 0;
  for(i = 0; i < sz; i++) {
    auto s = basic_new_heap();
    statespace_inputs_get(obj, i, s);

    std::string str = s->m->__str__();
    // TODO: Convert str here to Matlab Symbolic format.

    result[i] = new char[str.length() + 1];
    std::strcpy(result[i], str.c_str());

    basic_free_heap(s);
  }
}
void ml_statespace_inputs_set(StateSpace_C *obj, int len, const char** arg) {
  size_t sz = statespace_inputs_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert arg[i] here to SymEngine format. Pass the formatted string.
    basic_parse(s, arg[i]);

    if(i >= sz) {
      statespace_inputs_push_back(obj, s);
    } else {
      statespace_inputs_set(obj, i, s);
    }
  }
  basic_free_heap(s);
}
int ml_statespace_inputs_size(StateSpace_C *obj) {
  return statespace_inputs_size(obj);
}

void ml_statespace_f_get(StateSpace_C *obj, char **result) {
  size_t sz = statespace_f_size(obj);
  int i = 0;
  for(i = 0; i < sz; i++) {
    auto s = basic_new_heap();
    statespace_f_get(obj, i, s);

    std::string str = s->m->__str__();
    // TODO: Convert str here to Matlab Symbolic format.

    result[i] = new char[str.length() + 1];
    std::strcpy(result[i], str.c_str());

    basic_free_heap(s);
  }
}
void ml_statespace_f_set(StateSpace_C *obj, int len, const char** arg) {
  size_t sz = statespace_f_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert arg[i] here to SymEngine format. Pass the formatted string.
    basic_parse(s, arg[i]);

    if(i >= sz) {
      statespace_f_push_back(obj, s);
    } else {
      statespace_f_set(obj, i, s);
    }
  }
  basic_free_heap(s);
}
int ml_statespace_f_size(StateSpace_C *obj) {
  return statespace_f_size(obj);
}

void ml_statespace_g_get(StateSpace_C *obj, char **result) {
  size_t sz = statespace_g_size(obj);
  int i = 0;
  for(i = 0; i < sz; i++) {
    auto s = basic_new_heap();
    statespace_g_get(obj, i, s);

    std::string str = s->m->__str__();
    // TODO: Convert str here to Matlab Symbolic format.

    result[i] = new char[str.length() + 1];
    std::strcpy(result[i], str.c_str());

    basic_free_heap(s);
  }
}
void ml_statespace_g_set(StateSpace_C *obj, int len, const char** arg) {
  size_t sz = statespace_g_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert arg[i] here to SymEngine format. Pass the formatted string.
    basic_parse(s, arg[i]);

    if(i >= sz) {
      statespace_g_push_back(obj, s);
    } else {
      statespace_g_set(obj, i, s);
    }
  }
  basic_free_heap(s);
}
int ml_statespace_g_size(StateSpace_C *obj) {
  return statespace_g_size(obj);
}

// Get state matrix.
void ml_statespace_A_get(StateSpace_C *obj, char **result) {
  size_t n = statespace_states_size(obj);
  size_t fn = statespace_f_size(obj);

  // Matrix dimensions must be square.
  if(n == 0 || n != fn) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(n, n);
  statespace_A_get(obj, mat);

  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < n; i++) { // rows
    for (j = 0; j < n; j++) { // cols
      dense_matrix_get_basic(s, mat, j, i);

      std::string str = s->m->__str__();
      // TODO: Convert str here to Matlab Symbolic format.

      result[idx] = new char[str.length() + 1];
      std::strcpy(result[idx], str.c_str());
      idx++;

    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
}

// Get input matrix.
void ml_statespace_B_get(StateSpace_C *obj, char **result) {
  size_t n = statespace_states_size(obj);
  size_t m = statespace_inputs_size(obj);
  size_t fn = statespace_f_size(obj);

  // Number of inputs must be greater than 0.
  if(n == 0 || m == 0 || n != fn) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(n, m);
  statespace_B_get(obj, mat);

  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < n; i++) { // rows
    for (j = 0; j < m; j++) { // cols
      dense_matrix_get_basic(s, mat, i, j);

      std::string str = s->m->__str__();
      // TODO: Convert str here to Matlab Symbolic format.

      result[idx] = new char[str.length() + 1];
      std::strcpy(result[idx], str.c_str());
      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
}

// Get output matrix.
void ml_statespace_C_get(StateSpace_C *obj, char **result) {
  size_t n = statespace_states_size(obj);
  size_t p = statespace_g_size(obj);

  // Number of output equations must be greater than 0.
  if(n == 0 || p == 0) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(p, n);
  statespace_C_get(obj, mat);

  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < p; i++) { // rows
    for (j = 0; j < n; j++) { // cols
      dense_matrix_get_basic(s, mat, i, j);

      std::string str = s->m->__str__();
      // TODO: Convert str here to Matlab Symbolic format.

      result[idx] = new char[str.length() + 1];
      std::strcpy(result[idx], str.c_str());
      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
}

// Get feed-through matrix.
void ml_statespace_D_get(StateSpace_C *obj, char **result) {
  size_t m = statespace_inputs_size(obj);
  size_t p = statespace_g_size(obj);

  // Number of inputs & output equations must be greater than 0.
  if(m == 0 || p == 0) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(p, m);
  statespace_D_get(obj, mat);

  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < p; i++) { // rows
    for (j = 0; j < m; j++) { // cols
      dense_matrix_get_basic(s, mat, i, j);

      std::string str = s->m->__str__();
      // TODO: Convert str here to Matlab Symbolic format.

      result[idx] = new char[str.length() + 1];
      std::strcpy(result[idx], str.c_str());
      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
}

void ml_statespace_subs(StateSpace_C *obj,
                        int len,
                        const char **a,
                        const char **b) {

  // TODO: Exception handling.
  auto s_key = basic_new_heap();
  auto s_map = basic_new_heap();

  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert argument to SymEngine format.
    basic_parse(s_key, a[i]);
    basic_parse(s_map, b[i]);

    statespace_subs(obj, s_key, s_map);
  }

  basic_free_heap(s_key);
  basic_free_heap(s_map);
}

void ml_statespace_linearize(StateSpace_C *obj) {
  statespace_linearize(obj);
}

// Get controllability matrix.
void ml_statespace_ctrb(StateSpace_C *obj, char **result) {
  size_t n = statespace_states_size(obj);
  size_t m = statespace_inputs_size(obj);
  size_t fn = statespace_f_size(obj);

  // Matrix dimensions must be square.
  if(n == 0 || m == 0 || n != fn) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(n, n*m);
  statespace_ctrb(obj, mat);

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < n*m; i++) { // rows
    for(j = 0; j < n; j++) { // cols
      auto s = basic_new_heap();
      dense_matrix_get_basic(s, mat, j, i);

      std::string str = s->m->__str__();
      // TODO: Convert str here to Matlab Symbolic format.

      result[idx] = new char[str.length() + 1];
      std::strcpy(result[idx], str.c_str());
      idx++;

      basic_free_heap(s);
    }
  }

  dense_matrix_free(mat);
}

// Get observability matrix.
void ml_statespace_obsv(StateSpace_C *obj, char **result) {
  size_t n = statespace_states_size(obj);
  size_t fn = statespace_f_size(obj);
  size_t p = statespace_g_size(obj);

  // Matrix dimensions must be square.
  if(n == 0 || p == 0 || n != fn) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(n*p, n);
  statespace_obsv(obj, mat);

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < n; i++) { // rows
    for(j = 0; j < n*p; j++) { // cols
      auto s = basic_new_heap();
      dense_matrix_get_basic(s, mat, j, i);

      std::string str = s->m->__str__();
      // TODO: Convert str here to Matlab Symbolic format.

      result[idx] = new char[str.length() + 1];
      std::strcpy(result[idx], str.c_str());
      idx++;

      basic_free_heap(s);
    }
  }

  dense_matrix_free(mat);
}

// ----------------------------------------------------------------------
// MDP wrapper functions.
//
MDP_C* ml_mdp_new() {
  return mdp_new();
}

void ml_mdp_free(MDP_C* obj) {
  mdp_free(obj);
}

int ml_mdp_get_num_states(MDP_C* obj) {
  return mdp_num_states_get(obj);
}
void ml_mdp_set_num_states(MDP_C* obj, int arg) {
  mdp_num_states_set(obj, arg);
}

int ml_mdp_get_num_inputs(MDP_C* obj) {
  return mdp_num_inputs_get(obj);
}
void ml_mdp_set_num_inputs(MDP_C* obj, int arg) {
  mdp_num_inputs_set(obj, arg);
}

double ml_mdp_get_gamma(MDP_C* obj) {
  return mdp_gamma_get(obj);
}
void ml_mdp_set_gamma(MDP_C* obj, double arg) {
  mdp_gamma_set(obj, arg);
}


} // C
