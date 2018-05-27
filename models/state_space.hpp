#ifndef MODELS_STATE_SPACE_HPP
#define MODELS_STATE_SPACE_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/symbol.h>
#include <symengine/matrix.h>

#include "system.hpp"

namespace Controls {

class StateSpace : public Controls::System {
public:
  StateSpace();
  ~StateSpace();

  void set_states(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg);
  void set_inputs(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg);
  void set_f(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg);
  void set_g(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg);

  // void add_state(const SymEngine::RCP<const SymEngine::Basic> &arg);
  // void add_input(const SymEngine::RCP<const SymEngine::Basic> &arg);
  // void add_f(const SymEngine::RCP<const SymEngine::Basic> &arg);
  // void add_g(const SymEngine::RCP<const SymEngine::Basic> &arg);

  std::vector<SymEngine::RCP<const SymEngine::Basic>> get_states();
  std::vector<SymEngine::RCP<const SymEngine::Basic>> get_inputs();
  std::vector<SymEngine::RCP<const SymEngine::Basic>> get_f();
  std::vector<SymEngine::RCP<const SymEngine::Basic>> get_g();

  // SymEngine::DenseMatrix get_A_matrix();
  // SymEngine::DenseMatrix get_B_matrix();
  // SymEngine::DenseMatrix get_C_matrix();
  // SymEngine::DenseMatrix get_D_matrix();

private:
  // Vector of symbolic state variables.
  std::vector<SymEngine::RCP<const SymEngine::Basic>> states_;

  // Vector of symbolic input variables.
  std::vector<SymEngine::RCP<const SymEngine::Basic>> inputs_;

  // Vector of state equations.
  std::vector<SymEngine::RCP<const SymEngine::Basic>> f_;

  // Vector of output equations.
  std::vector<SymEngine::RCP<const SymEngine::Basic>> g_;
};

} // Controls

#endif /* end of include guard: MODELS_STATE_SPACE_HPP */
