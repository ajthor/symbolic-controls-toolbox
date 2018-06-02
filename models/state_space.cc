#include <vector>
#include <symengine/add.h>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>
#include <symengine/symbol.h>
#include <symengine/subs.h>

#include "state_space.hpp"

namespace Controls {

StateSpace::StateSpace() {}

StateSpace::~StateSpace() {}

void StateSpace::add_state(const SymEngine::RCP<const SymEngine::Basic> arg) {
  states_.push_back(arg);
}
void StateSpace::set_state(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg) {
  states_.at(n) = arg;
}
SymEngine::RCP<const SymEngine::Basic> StateSpace::get_state(size_t n) {
  return states_.at(n);
}
size_t StateSpace::get_num_states() {
  return states_.size();
}

void StateSpace::add_input(const SymEngine::RCP<const SymEngine::Basic> arg) {
  inputs_.push_back(arg);
}
void StateSpace::set_input(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg) {
  inputs_.at(n) = arg;
}
SymEngine::RCP<const SymEngine::Basic> StateSpace::get_input(size_t n) {
  return inputs_.at(n);
}
size_t StateSpace::get_num_inputs() {
  return inputs_.size();
}

void StateSpace::add_f(const SymEngine::RCP<const SymEngine::Basic> arg) {
  f_.push_back(arg);
}
void StateSpace::set_f(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg) {
  f_.at(n) = arg;
}
SymEngine::RCP<const SymEngine::Basic> StateSpace::get_f(size_t n) {
  return f_.at(n);
}
size_t StateSpace::get_num_f() {
  return f_.size();
}

void StateSpace::add_g(const SymEngine::RCP<const SymEngine::Basic> arg) {
  g_.push_back(arg);
}
void StateSpace::set_g(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg) {
  g_.at(n) = arg;
}
SymEngine::RCP<const SymEngine::Basic> StateSpace::get_g(size_t n) {
  return g_.at(n);
}
size_t StateSpace::get_num_g() {
  return g_.size();
}

void StateSpace::get_A_matrix(SymEngine::DenseMatrix &result) {
  unsigned n = states_.size();
  SymEngine::DenseMatrix f;
  SymEngine::DenseMatrix x;

  result = SymEngine::DenseMatrix(n, n);

  if(n > 0 && f_.size() == n) {
    f = SymEngine::DenseMatrix(n, 1, {f_});
    x = SymEngine::DenseMatrix(n, 1, {states_});

    jacobian(f, x, result);
  }
}
void StateSpace::get_B_matrix(SymEngine::DenseMatrix &result) {
  unsigned n = states_.size();
  unsigned m = inputs_.size();
  SymEngine::DenseMatrix f;
  SymEngine::DenseMatrix u;

  result = SymEngine::DenseMatrix(n, m);

  if(n > 0 && f_.size() == n && m > 0) {
    f = SymEngine::DenseMatrix(n, 1, {f_});
    u = SymEngine::DenseMatrix(m, 1, {inputs_});

    jacobian(f, u, result);
  }
}
void StateSpace::get_C_matrix(SymEngine::DenseMatrix &result) {
  unsigned n = states_.size();
  unsigned p = g_.size();
  SymEngine::DenseMatrix g;
  SymEngine::DenseMatrix x;

  result = SymEngine::DenseMatrix(p, n);

  if(n > 0 && p > 0) {
    g = SymEngine::DenseMatrix(p, 1, {g_});
    x = SymEngine::DenseMatrix(n, 1, {states_});

    jacobian(g, x, result);
  }
}
void StateSpace::get_D_matrix(SymEngine::DenseMatrix &result) {
  unsigned m = inputs_.size();
  unsigned p = g_.size();
  SymEngine::DenseMatrix g;
  SymEngine::DenseMatrix u;

  result = SymEngine::DenseMatrix(p, m);

  if(m > 0 && p > 0) {
    g = SymEngine::DenseMatrix(p, 1, {g_});
    u = SymEngine::DenseMatrix(m, 1, {inputs_});

    jacobian(g, u, result);
  }
}

void StateSpace::subs(const SymEngine::RCP<const SymEngine::Basic> key,
                      const SymEngine::RCP<const SymEngine::Basic> map) {

  SymEngine::map_basic_basic d;
  d[key] = map;

  int i = 0;
  for(i = 0; i < f_.size(); i++) {
    f_[i] = SymEngine::ssubs(f_[i], d);
  }

  for(i = 0; i < g_.size(); i++) {
    g_[i] = SymEngine::ssubs(g_[i], d);
  }
}

void StateSpace::linearize() {
  size_t n = states_.size();
  size_t m = inputs_.size();
  size_t p = g_.size();

  SymEngine::map_basic_basic d;

  for(auto e : states_) {
    d[e] = SymEngine::integer(0);
  }

  for(auto e : inputs_) {
    d[e] = SymEngine::integer(0);
  }

  SymEngine::DenseMatrix A, B, C, D, x, u, M, R;
  get_A_matrix(A);
  get_B_matrix(B);
  get_C_matrix(C);
  get_D_matrix(D);

  int i = 0;
  int j = 0;
  for(i = 0; i < A.nrows(); i++) { // rows
    for(j = 0; j < A.ncols(); j++) { // cols
      A.set(i, j, SymEngine::ssubs(A.get(i, j), d));
    }
  }
  for(i = 0; i < B.nrows(); i++) { // rows
    for(j = 0; j < B.ncols(); j++) { // cols
      B.set(i, j, SymEngine::ssubs(B.get(i, j), d));
    }
  }
  for(i = 0; i < C.nrows(); i++) { // rows
    for(j = 0; j < C.ncols(); j++) { // cols
      C.set(i, j, SymEngine::ssubs(C.get(i, j), d));
    }
  }
  for(i = 0; i < D.nrows(); i++) { // rows
    for(j = 0; j < D.ncols(); j++) { // cols
      D.set(i, j, SymEngine::ssubs(D.get(i, j), d));
    }
  }

  x = SymEngine::DenseMatrix(n, 1, {states_});
  u = SymEngine::DenseMatrix(m, 1, {inputs_});

  M = SymEngine::DenseMatrix(n, 1);
  R = SymEngine::DenseMatrix(n, 1);
  A.mul_matrix(x, M);
  B.mul_matrix(u, R);
  M.add_matrix(R, M);
  f_ = M.as_vec_basic();

  // for(i = 0; i < A.nrows(); i++) {
    // R = SymEngine::DenseMatrix(1, M.ncols());
    // M.submatrix(R, i, 0, i, M.ncols() - 1);
    // printf("A.ncols %d\n", A.ncols());
    // printf("R\n%s\n", R.__str__().c_str());
    // f_.at(i) = SymEngine::add(M.as_vec_basic());

    // f_[i] = M.get(i, 1);
  // }
  // M.add_matrix(R, M);
  // f_ = M.as_vec_basic();

  M = SymEngine::DenseMatrix(p, 1);
  R = SymEngine::DenseMatrix(p, 1);
  C.mul_matrix(x, M);
  D.mul_matrix(u, R);
  M.add_matrix(R, M);
  g_ = M.as_vec_basic();
}
// void linearize(SymEngine::vec_basic &eq) {
// //   // TODO: Size checking. Number of equilibrium points must equal number of states & inputs.
// //
// //
// //   // int i = 0;
// //   // for(i = 0; i < states_.size(); i++) {
// //   //   f_[i] = SymEngine::ssubs(states_[i], eq[i]);
// //   // }
// //   //
// //   // for(i = states_.size(); i < eq.size(); i++) {
// //   //   f_[i] = SymEngine::ssubs()
// //   // }
// }

} // Controls
