#ifndef SYMCTRL_MDP_HPP
#define SYMCTRL_MDP_HPP

#include <map>
#include <tuple>
#include <vector>

#include "control_model.hpp"

namespace Controls {

class MDPVisitor;

class MDP : public ControlModel {
protected:
  // TODO: Eventually, this should change to CSR format, though I haven't
  // figured out how to do CSR with >2d matrices.
  typedef std::map<std::tuple<size_t, size_t>, double> mdp_sparse_t;

private:
  size_t num_states_;
  size_t num_inputs_;

  double gamma_;

  void set_num_states(const size_t arg);
  void set_num_inputs(const size_t arg);

public:
  MDP(const size_t x, const size_t u);
  ~MDP();

  size_t get_num_states();
  size_t get_num_inputs();

  void set_gamma(const double arg);
  double get_gamma();

  // P & R are X x X' x U.
  // This is stored as a vector (U) of sparse adjacency matrices (X x X').
  std::vector<mdp_sparse_t> probabilities_;
  std::vector<mdp_sparse_t> rewards_;

  void set_probability(size_t u, size_t x, size_t xp, const double value);
  double get_probability(size_t u, size_t x, size_t xp);

  void set_reward(size_t u, size_t x, size_t xp, const double value);
  double get_reward(size_t u, size_t x, size_t xp);

  void accept(MDPVisitor &visitor);
};

} // Controls

#endif /* end of include guard: SYMCTRL_MDP_HPP */
