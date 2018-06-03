#ifndef SYMCTRL_MDP_HPP
#define SYMCTRL_MDP_HPP

#include "control_model.hpp"
#include "utils/sparse_matrix.hpp"

namespace Controls {

class MDP : public ControlModel {
public:
  MDP();
  // MDP(const std::size_t x, const std::size_t u, const double g);
  ~MDP();

  void set_num_states(const std::size_t arg);
  void set_num_inputs(const std::size_t arg);
  void set_gamma(const double arg);

  std::size_t get_num_states();
  std::size_t get_num_inputs();
  double get_gamma();

private:
  std::size_t num_states_;
  std::size_t num_inputs_;

  SparseMatrix<double> probabilities_ = SparseMatrix<double>();
  SparseMatrix<double> rewards_ = SparseMatrix<double>();

  double gamma_;
};

} // Controls

#endif /* end of include guard: SYMCTRL_MDP_HPP */
