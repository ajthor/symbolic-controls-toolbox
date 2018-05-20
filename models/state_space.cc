#include "state_space.hpp"

using Controls::StateSpace;

namespace Controls {

StateSpace::StateSpace() {}

StateSpace::~StateSpace() {}

void StateSpace::set_states(const std::vector<RCP<const Basic>> &arg) {
  states_ = arg;
}

std::vector<RCP<const Basic>> StateSpace::get_states() {
  return states_;
}

// void StateSpace::set_inputs(const std::vector<RCP<const Basic>> &arg) {
//   inputs_ = arg;
// }
//
// void StateSpace::add_state(const RCP<const Basic> &arg) {
//   states_.insert(states_.end(), arg.begin(), arg.end());
// }
//
// void StateSpace::add_input(const RCP<const Basic> &arg) {
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
