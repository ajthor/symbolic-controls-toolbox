#ifndef CONTROL_MODELS_STATE_SPACE_HPP
#define CONTROL_MODELS_STATE_SPACE_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/symbol.h>
#include <symengine/matrix.h>

#include "system.hpp"

using SymEngine::Basic;
using SymEngine::DenseMatrix;
using SymEngine::Symbol;
using SymEngine::RCP;

namespace Controls {

class StateSpace : public System {
public:
  StateSpace();
  ~StateSpace();

  void set_states(const std::vector<RCP<const Symbol>> &arg);
  // void set_inputs(const std::vector<RCP<const Symbol>> &arg);
  // void set_f(const std::vector<RCP<const Basic>> &arg);
  // void set_g(const std::vector<RCP<const Basic>> &arg);
  //
  // void add_state(const RCP<const Symbol> &arg);
  // void add_input(const RCP<const Symbol> &arg);
  // void add_f(const RCP<const Basic> &arg);
  // void add_g(const RCP<const Basic> &arg);

  std::vector<RCP<const Symbol>> get_states();
  // std::vector<RCP<const Symbol>> get_inputs();
  // std::vector<RCP<const Basic>> get_f();
  // std::vector<RCP<const Basic>> get_g();
  //
  // DenseMatrix get_A_matrix();
  // DenseMatrix get_B_matrix();
  // DenseMatrix get_C_matrix();
  // DenseMatrix get_D_matrix();

private:
  // Vector of symbolic state variables.
  std::vector<RCP<const Symbol>> states_;

  // Vector of symbolic inputs.
  std::vector<RCP<const Symbol>> inputs_;

  std::vector<RCP<const Basic>> f_;
  std::vector<RCP<const Basic>> g_;
};

} // Controls

#endif /* end of include guard: CONTROL_MODELS_STATE_SPACE_HPP */
