#ifndef SYMCTRL_MDP_HPP
#define SYMCTRL_MDP_HPP

#include <map>
#include <tuple>
#include <type_traits>
#include <vector>

#include "system.hpp"
#include "cost_function.hpp"
#include "transition_function.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// MDP
//
// Markov Decision Process
//
// The MDP model uses a functional model to denote the transition probabilities
// and reward function. The transition probabilities and rewards, which are the
// fundamental components of the MDP model are divided into two possible
// categories, depending on whether the state space is discretized or
// continuous.
//
// The state transition has a probability given by:
//
//     P: X x U x X' -> [0, 1]
//
// The reward function is an expectation given by:
//
//     R: X x U x X' -> Reals
//
// This means we can use either a functional model for every (X, U, X') tuple
// to denote a given probability or reward, or a linear mapping using a
// discrete set of states.
//
// In theory, the above function definitions use (X, U, X') as function
// parameters. However, in practice, the transition probabilities are given as
// a probability distribution given a state X and taking action U. The rewards,
// similarly, are a function that returns a real value given a state X and
// taking action U. This does not take into account the resulting state X',
// because the MDP model has no intuition over whether the state will actually
// reach the desired state X' outside of the transition probabilities.
//
// In the discretized case, the transition probability matrix has elements
// which are of the form P{x'| x, u}, which denotes the conditional probability
// of transferring to state x' given the discrete state x and discrete action
// u. The reward matrix has elements of the form E{x'|x, u}, which denotes the
// expected reward for reaching state x' given x and u.
class MDP : public System {
private:
  size_t nstates_;
  size_t ninputs_;

  CostFunction *cost_function_;
  TransitionFunction *transition_kernel_;

  double gamma_;

public:
  MDP(const size_t nstates,
      const size_t ninputs,
      CostFunction *R,
      TransitionFunction *T,
      const double gamma) :
      nstates_(nstates),
      ninputs_(ninputs),
      cost_function_(R),
      transition_kernel_(T),
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
// Partially-Observable Markov Decision Process
class POMDP : public MDP {
private:
  TransitionFunction *observation_kernel_;

public:
  POMDP(const size_t nstates,
        const size_t ninputs,
        CostFunction *R,
        TransitionFunction *T,
        TransitionFunction *Ob,
        const double gamma) :
        MDP{nstates, ninputs, R, T, gamma},
        observation_kernel_(Ob) {}

  ~POMDP() {}

  void accept(Visitor &visitor);
};

} // Controls

#endif /* end of include guard: SYMCTRL_MDP_HPP */
