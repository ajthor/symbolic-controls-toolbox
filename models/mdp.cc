#include "mdp.hpp"

using Controls::MDP;

namespace Controls {

MDP::MDP() {};

MDP::MDP(const std::size_t x, const std::size_t u, const double gamma) {
  set_num_states(x);
  set_num_inputs(u);
  set_gamma(gamma);
}

MDP::~MDP() {}

void MDP::set_num_states(const std::size_t arg) {
  num_states_ = arg;
}

void MDP::set_num_inputs(const std::size_t arg) {
  num_inputs_ = arg;
}

void MDP::set_gamma(const double arg) {
  gamma_ = arg;
}

std::size_t MDP::get_num_states() {
  return num_states_;
}

std::size_t MDP::get_num_inputs() {
  return num_inputs_;
}

double MDP::get_gamma() {
  return gamma_;
}

} // Controls
