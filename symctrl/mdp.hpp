#ifndef SYMCTRL_MDP_HPP
#define SYMCTRL_MDP_HPP

#include <vector>

#include <symengine/sets.h>

#include "system.hpp"
#include "cost_function.hpp"
#include "transition_function.hpp"

using SymEngine::RCP;
using SymEngine::Set;

namespace Controls {

class ControlPolicyVisitor;

// ----------------------------------------------------------------------
// ControlPolicy
//
class ControlPolicy {
private:
  virtual void calc(const std::vector<double> &state,
                    const std::vector<double> &input,
                    std::vector<double> *result) = 0;

public:
  ControlPolicy();
  ~ControlPolicy();

  void eval(const std::vector<double> &state,
            const std::vector<double> &input,
            std::vector<double> *result) {
    //
    calc(state, input, result);
  }

  virtual void accept(ControlPolicyVisitor &visitor) = 0;
};

// ----------------------------------------------------------------------
// ControlPolicy Visitor
//
class ControlPolicyVisitor {
public:
  virtual void visit(ControlPolicy &m) = 0;
};

// ----------------------------------------------------------------------
// Discrete ControlPolicy
//
class DiscreteControlPolicy : public ControlPolicy {
private:
  void calc(const std::vector<double> &state,
            const std::vector<double> &input,
            std::vector<double> *result) {
    //
  }

  Controls::DenseMatrix<double> *policy_matrix_;

public:
  DiscreteControlPolicy(const size_t nstates,
                        const size_t ninputs) {
    policy_matrix_ = new Controls::DenseMatrix<double>(nstates, ninputs);
  }
  ~DiscreteControlPolicy() {}

  void accept(ControlPolicyVisitor &visitor) {
    visitor.visit(*this);
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

  // size_t nstates() const { return nstates_; }
  // size_t ninputs() const { return ninputs_; }
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
