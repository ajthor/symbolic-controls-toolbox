#include "visitor.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Policy Iteration Visitor
//
class PolicyIterationVisitor : public SystemVisitor<PolicyIterationVisitor> {
private:
  ControlPolicy *policy_;

public:
  PolicyIterationVisitor(ControlPolicy *policy) : policy_(policy) {}

  void visit(MDP &m) {}
  void visit(POMDP &m) {}
  void visit(System &m) {}
};

void policy_iteration(MDP &m, ControlPolicy *policy) {
  PolicyIterationVisitor v(policy);
  m.accept(v);
}

// ----------------------------------------------------------------------
// Value Iteration Visitor
//
class ValueIterationVisitor : public SystemVisitor<ValueIterationVisitor> {
private:
  ControlPolicy *policy_;

public:
  ValueIterationVisitor(ControlPolicy *policy) : policy_(policy) {}

  void visit(MDP &m) {}
  void visit(POMDP &m) {}
  void visit(System &m) {}
};

void value_iteration(MDP &m, ControlPolicy *policy) {
  ValueIterationVisitor v(policy);
  m.accept(v);
}

// MDP::MDP(const size_t x, const size_t u) {
//   num_states_ = x;
//   num_inputs_ = u;
//   gamma_ = 0.0;
//
//   probabilities_ = mdp_sparse_t(u);
//   rewards_ = mdp_sparse_t(u);
// };
// MDP::~MDP() {}
//
// size_t MDP::nstates() {
//   return nstates_;
// }
//
// size_t MDP::ninputs() {
//   return ninputs_;
// }
//
// void MDP::set_probability(size_t u, size_t x, size_t xp, double value) {
//   // TODO: Ensure u is not greater than num_inputs.
//   // TODO: Ensure x is not greater than num_states.
//   // TODO: Ensure xp is not greater than num_states.
//
//   // TODO: Ensure probability is not greater than 1.
//   // TODO: Ensure probability of any one row is not greater than 1.
//
//   probabilities_.at(u).set(x, xp, value);
// }
// double MDP::get_probability(size_t u, size_t x, size_t xp) {
//   // TODO: Ensure u is not greater than num_inputs.
//   // TODO: Ensure x is not greater than num_states.
//   // TODO: Ensure xp is not greater than num_states.
//
//   // try {
//   //   return probabilities_.at(u).at(std::make_tuple(x, xp));
//   // } catch(const std::out_of_range &e) {
//   //   return 0.0;
//   // }
//
//   auto n_map = probabilities_.at(u);
//   auto idx = std::make_tuple(x, xp);
//
//   auto res = n_map.find(idx);
//   if(res != n_map.end()) {
//     return res->second;
//   } else {
//     return 0;
//   }
// }
//
// void MDP::set_reward(size_t u, size_t x, size_t xp, double value) {
//   // TODO: Ensure u is not greater than num_inputs.
//   // TODO: Ensure x is not greater than num_states.
//   // TODO: Ensure xp is not greater than num_states.
//
//   rewards_.at(u).set(x, xp, value);
// }
// double MDP::get_reward(size_t u, size_t x, size_t xp) {
//   // TODO: Ensure u is not greater than num_inputs.
//   // TODO: Ensure x is not greater than num_states.
//   // TODO: Ensure xp is not greater than num_states.
//
//   // try {
//   //   return rewards_.at(u).at(std::make_tuple(x, xp));
//   // } catch(const std::out_of_range &e) {
//   //   return 0.0;
//   // }
//
//   auto n_map = rewards_.at(u);
//   auto idx = std::make_tuple(x, xp);
//
//   auto res = n_map.find(idx);
//   if(res != n_map.end()) {
//     return res->second;
//   } else {
//     return 0;
//   }
// }
//
// void MDP::set_gamma(const double arg) {
//   gamma_ = arg;
// }
// double MDP::get_gamma() {
//   return gamma_;
// }

} // Controls
