#ifndef MODELS_STATE_SPACE_HPP
#define MODELS_STATE_SPACE_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/symbol.h>
#include <symengine/matrix.h>
#include <symengine/add.h>
#include <symengine/pow.h>

#include "system.hpp"

namespace Controls {

// StateSpace Class
class StateSpace : public Controls::System {
public:
  StateSpace();
  ~StateSpace();

  void add_state(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_state(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_state(size_t n);
  size_t get_num_states();

  void add_input(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_input(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_input(size_t n);
  size_t get_num_inputs();

  void add_f(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_f(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_f(size_t n);
  size_t get_num_f();

  void add_g(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_g(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_g(size_t n);
  size_t get_num_g();

  // void set_inputs(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg);

  // void set_f(const std::vector<SymEngine::RCP<const SymEngine::Basic>> arg);
  // void set_g(const std::vector<SymEngine::RCP<const SymEngine::Basic>> arg);

  // void add_state(const SymEngine::RCP<const SymEngine::Basic> &arg);
  // void add_input(const SymEngine::RCP<const SymEngine::Basic> &arg);
  // void add_f(const SymEngine::RCP<const SymEngine::Basic> &arg);
  // void add_g(const SymEngine::RCP<const SymEngine::Basic> &arg);

  // std::vector<SymEngine::RCP<const SymEngine::Basic>> get_inputs();
  // std::vector<SymEngine::RCP<const SymEngine::Basic>> get_f();
  // std::vector<SymEngine::RCP<const SymEngine::Basic>> get_g();

  void get_A_matrix(SymEngine::DenseMatrix &result);
  void get_B_matrix(SymEngine::DenseMatrix &result);
  void get_C_matrix(SymEngine::DenseMatrix &result);
  void get_D_matrix(SymEngine::DenseMatrix &result);

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
