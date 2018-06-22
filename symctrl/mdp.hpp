#ifndef SYMCTRL_MDP_HPP
#define SYMCTRL_MDP_HPP

#include <map>
#include <tuple>
#include <type_traits>
#include <vector>

#include "control_model.hpp"
#include "matrix/sparse.hpp"

namespace Controls {

class MDPVisitor;

template<typename Derived>
class MDPBase : public ControlModel {
private:
  double gamma_ = 0.0;

public:
  void set_gamma(const double arg) : gamma_(arg) {}
  double get_gamma() {
    return gamma_;
  }

  void accept(MDPVisitor &visitor) {
    visitor.visit(static_cast<const Derived&>(*this));
  }
};

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
template<ModelDataType T = Discrete>
class MDP : public MDPBase<MDP> {
private:
  typedef double (*p_func)(std::vector<T> x,
                           std::vector<T> u,
                           std::vector<T> xp) probability_fun_t;

  typedef double (*r_func)(std::vector<T> x,
                           std::vector<T> u,
                           std::vector<T> xp) reward_fun_t;

  size_t states_;
  size_t inputs_;

  // TODO: Eventually, this should change to CSR format, though I haven't
  // figured out how to do CSR with >2d matrices.
  // typedef std::map<std::tuple<size_t, size_t>, double> mdp_sparse_t;
  typedef std::vector<CSRMatrix<double>> mdp_sparse_t;

  // P & R are X x U x X'.
  // This is stored as a vector (U) of sparse adjacency matrices (X x X').
  mdp_sparse_t probabilities_;
  mdp_sparse_t rewards_;

public:
  MDP(const size_t nx, const size_t nu);
  ~MDP();

  size_t nstates() const { return states_; }
  size_t ninputs() const { return inputs_; }

  void set_probability(size_t x, size_t u, size_t xp, const double value);
  double get_probability(size_t x, size_t u, size_t xp);

  void set_reward(size_t x, size_t u, size_t xp, const double value);
  double get_reward(size_t x, size_t u, size_t xp);
};

template<>
class MDP<Continuous> : public MDPBase {
private:

public:
  MDP() {}
  ~MDP() {}
};

// ----------------------------------------------------------------------
// POMDP
//
// Partially-Observable Markov Decision Process
template<ModelDataType T = Discrete>
class POMDP : public MDP<T> {
public:
  POMDP(const size_t x, const size_t u) : MDP<T>(x, u) {}
  ~POMDP() {}

  void accept(MDPVisitor &visitor);
};

template<>
class POMDP<Continuous> : public MDP<Continuous> {

};

} // Controls

#endif /* end of include guard: SYMCTRL_MDP_HPP */
