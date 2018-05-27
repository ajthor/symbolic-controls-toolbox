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

  void set_num_states(unsigned int arg);
  void set_num_inputs(unsigned int arg);
  void set_gamma(double arg);

  unsigned int get_num_states();
  unsigned int get_num_inputs();
  double get_gamma();

private:
  unsigned int num_states_;
  unsigned int num_inputs_;

  // SparseMatrix<double> probabilities_;
  // SparseMatrix<double> rewards_;

  double gamma_;
};

} // Controls

#endif /* end of include guard: MODELS_MDP_HPP */
