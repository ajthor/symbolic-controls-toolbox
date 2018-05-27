#include "mdp.hpp"

using Controls::MDP;

namespace Controls {

MDP::MDP() {}
MDP::~MDP() {}

void MDP::set_num_states(unsigned int arg) {
  num_states_ = arg;
}

void MDP::set_num_inputs(unsigned int arg) {
  num_inputs_ = arg;
}

void MDP::set_gamma(double arg) {
  gamma_ = arg;
}

unsigned int MDP::get_num_states() {
  return num_states_;
}

unsigned int MDP::get_num_inputs() {
  return num_inputs_;
}

double MDP::get_gamma() {
  return gamma_;
}

} // Controls
