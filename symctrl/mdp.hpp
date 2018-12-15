#ifndef SYMCTRL_MDP_HPP
#define SYMCTRL_MDP_HPP

#include <vector>

#include <symengine/sets.h>

#include "system.hpp"
#include "matrix/dense.hpp"
#include "cost_function.hpp"
#include "transition_function.hpp"
#include "function.hpp"

using SymEngine::RCP;
using SymEngine::Set;

typedef Controls::Function<const std::vector<double> &,
                           std::vector<double> &> control_policy;
//

namespace Controls {

// ----------------------------------------------------------------------
// ControlPolicy
//
class ControlPolicy :
public Controls::BaseFunction<ControlPolicy,
                              const std::vector<double> &,
                              std::vector<double> &> {
public:
  void eval(const std::vector<double> &state,
            std::vector<double> &result) = 0;
};

template<typename Fun>
inline control_policy *make_control_policy(Fun f) {
  return new Controls::LambdaFunction<Fun,
                                      const std::vector<double> &,
                                      std::vector<double> &>(f);
}
//

template<typename T>
inline bool is_a_control_policy(T &b) {
    return dynamic_cast<control_policy *>(&b) != nullptr;
}

// ----------------------------------------------------------------------
// Discrete ControlPolicy
//
class DiscreteControlPolicy :
public ControlPolicy, public Controls::DenseMatrix<double> {
public:
  DiscreteControlPolicy(const size_t n_states,
                        const size_t n_inputs) :
                        Controls::DenseMatrix<double>(n_states, n_inputs) {}
  ~DiscreteControlPolicy() {}

  void eval(const std::vector<double> &state,
            std::vector<double> &result) {
    //
    // Hash the state vector to come up with a unique identifier.
    // The identifier corresponds to a specific row in the matrix.
    // Return the result.
  }
};

// ----------------------------------------------------------------------
// MDP
//
class MDP : public System {
private:
  RCP<const Set> state_space_;
  RCP<const Set> input_space_;

  TransitionFunction *transition_kernel_;
  CostFunction *cost_function_;

  double gamma_;

public:
  MDP(RCP<const Set> state_space,
      RCP<const Set> input_space,
      TransitionFunction *T,
      CostFunction *R,
      const double gamma) :
      state_space_(state_space),
      input_space_(input_space),
      transition_kernel_(T),
      cost_function_(R),
      gamma_(gamma) {}

  ~MDP() {}

  // size_t n_states() const { return nstates_; }
  // size_t n_inputs() const { return ninputs_; }
  //
  // void set_transition_function(TransitionFunction *T);
  // TransitionFunction *get_transition_function();
  //
  // void set_cost_function(CostFunction &R);
  // CostFunction &get_cost_function();
  //
  // void set_gamma(const double arg) {
  //   gamma_ = (arg > 0 ? (arg < 1 ? arg : 1) : 0);
  // }
  // double get_gamma() { return gamma_; }

  void accept(Visitor &visitor);
};

// ----------------------------------------------------------------------
// POMDP
//
class POMDP : public MDP {
private:
  TransitionFunction *observation_kernel_;

public:
  POMDP(RCP<const Set> state_space,
        RCP<const Set> input_space,
        TransitionFunction *T,
        CostFunction *R,
        TransitionFunction *Ob,
        const double gamma) :
        MDP{state_space, input_space, T, R, gamma},
        observation_kernel_(Ob) {}

  ~POMDP() {}

  void accept(Visitor &visitor);
};

// ----------------------------------------------------------------------
// Policy Iteration
//
void policy_iteration(MDP &m, ControlPolicy *policy);

// ----------------------------------------------------------------------
// Value Iteration
//
void value_iteration(MDP &m, ControlPolicy *policy);

} // Controls

#endif /* end of include guard: SYMCTRL_MDP_HPP */
