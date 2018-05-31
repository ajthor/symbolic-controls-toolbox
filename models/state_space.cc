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


// void StateSpace::set_inputs(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg) {
//   inputs_ = arg;
// }
//
// void StateSpace::set_f(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg) {
//   f_ = arg;
// }
//
// void StateSpace::set_g(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg) {
//   g_ = arg;
// }
//
// std::vector<SymEngine::RCP<const SymEngine::Basic>> StateSpace::get_inputs() {
//   return inputs_;
// }
//
// std::vector<SymEngine::RCP<const SymEngine::Basic>> StateSpace::get_f() {
//   return f_;
// }
//
// std::vector<SymEngine::RCP<const SymEngine::Basic>> StateSpace::get_g() {
//   return g_;
// }


// void StateSpace::set_inputs(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg) {
//   inputs_ = arg;
// }
//
// void StateSpace::add_state(const SymEngine::RCP<const SymEngine::Basic> &arg) {
//   states_.insert(states_.end(), arg.begin(), arg.end());
// }
//
// void StateSpace::add_input(const SymEngine::RCP<const SymEngine::Basic> &arg) {
//   inputs_.insert(inputs_.end(), arg.begin(), arg.end());
// }

// DenseMatrix StateSpace::get_A_matrix() {
//   unsigned n = states_.size();
//
//   DenseMatrix X = DenseMatrix(n, 1, {states_});
//
//   DenseMatrix J = DenseMatrix(n, n);
//   jacobian(f_, X, J);
//
//   return J;
// }

// DenseMatrix StateSpace::get_B_matrix() {
//   unsigned n = states_.size();
//   unsigned m = inputs_.size();
//
//   DenseMatrix X = DenseMatrix(m, 1, {inputs_});
//
//   DenseMatrix J = DenseMatrix(n, m);
//   jacobian(f_, X, J);
//
//   return J;
// }

// DenseMatrix StateSpace::get_C_matrix() {
//   unsigned n = states_.size();
//   unsigned p = inputs_.size();
//
//   DenseMatrix X = DenseMatrix(n, 1, {states_});
//
//   DenseMatrix J = DenseMatrix(p, n);
//   jacobian(g_, X, J);
//
//   return J;
// }

// DenseMatrix StateSpace::get_D_matrix() {
//   unsigned m = inputs_.size();
//   unsigned p = g_.size();
//
//   DenseMatrix X = DenseMatrix(n, 1, {inputs_});
//
//   DenseMatrix J = DenseMatrix(p, m);
//   jacobian(g_, X, J);
//
//   return J;
// }

} // Controls
