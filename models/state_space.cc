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


void ctrb(StateSpace &obj, SymEngine::DenseMatrix &result) {
  unsigned n = obj.get_num_states();
  unsigned m = obj.get_num_inputs();

  SymEngine::DenseMatrix A;
  SymEngine::DenseMatrix B;
  SymEngine::DenseMatrix M;
  obj.get_A_matrix(A);
  obj.get_B_matrix(B);

  result = SymEngine::DenseMatrix(B);
  M = SymEngine::DenseMatrix(result);

  int k = 0;
  for(k = m; k < n*m; k += m) {
    // Keep a running matrix.
    A.mul_matrix(M, M);
    result.row_join(M);
  }
}

int ctrb_rank(StateSpace &obj) {
  SymEngine::DenseMatrix co;
  ctrb(obj, co);
  // 
  // SymEngine::permutelist pl;
  // SymEngine::pivoted_gaussian_elimination(co, result, pl);
  return co.rank();
}

void obsv(StateSpace &obj, SymEngine::DenseMatrix &result) {
  unsigned n = obj.get_num_states();
  unsigned p = obj.get_num_g();

  SymEngine::DenseMatrix A;
  SymEngine::DenseMatrix C;
  SymEngine::DenseMatrix M;
  obj.get_A_matrix(A);
  obj.get_C_matrix(C);

  result = SymEngine::DenseMatrix(C);
  M = SymEngine::DenseMatrix(result);

  int k = 0;
  for(k = p; k < n*p; k += p) {
    // Keep a running matrix.
    M.mul_matrix(A, M);
    result.col_join(M);
  }
}


} // Controls
