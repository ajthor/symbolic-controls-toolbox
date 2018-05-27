#ifndef MODELS_MDP_HPP
#define MODELS_MDP_HPP

#include "control_model.hpp"
#include "../utils/sparse_matrix.hpp"

using Controls::SparseMatrix;

namespace Controls {

class MDP : public ControlModel {
public:
  MDP();
  ~MDP();

  void set_num_states(int arg);
  void set_num_inputs(int arg);
  void set_gamma(double arg);

  int get_num_states();
  int get_num_inputs();
  double get_gamma();

private:
  int num_states_;
  int num_inputs_;

  // SparseMatrix<double> probabilities_;
  // SparseMatrix<double> rewards_;

  double gamma_;
};

} // Controls

#endif /* end of include guard: MODELS_MDP_HPP */
