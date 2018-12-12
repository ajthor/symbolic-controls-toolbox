// A hybrid system has several 'modes', where the dynamics of the system change.

#ifndef SYMCTRL_HYBRID_SYSTEM_HPP
#define SYMCTRL_HYBRID_SYSTEM_HPP

#include <map>
#include <tuple>
#include <vector>
#include <symengine/basic.h>
#include <symengine/matrix.h>

#include "system.hpp"

using SymEngine::Basic;
using SymEngine::RCP;

namespace Controls {

class HybridSystem : public System {
public:
  HybridSystem();
  ~HybridSystem();

  void add_state(const RCP<const Basic> arg);
  void set_state(size_t n, const RCP<const Basic> arg);
  RCP<const Basic> get_state(size_t n);
  // void remove_state(size_t n);
  size_t get_num_states();

  void add_input(const RCP<const Basic> arg);
  void set_input(size_t n, const RCP<const Basic> arg);
  RCP<const Basic> get_input(size_t n);
  // void remove_input(size_t n);
  size_t get_num_inputs();

  void add_f(const RCP<const Basic> arg);
  void set_f(size_t n, const RCP<const Basic> arg);
  RCP<const Basic> get_f(size_t n);
  // void remove_f(size_t n);
  size_t get_num_f();

  void add_g(const RCP<const Basic> arg);
  void set_g(size_t n, const RCP<const Basic> arg);
  RCP<const Basic> get_g(size_t n);
  // void remove_g(size_t n);
  size_t get_num_g();

  void set_num_modes(size_t r, size_t c, const RCP<const Basic> arg);
  RCP<const Basic> get_num_modes(size_t r, size_t c);

  void set_guard(size_t r, size_t c, const RCP<const Basic> arg);
  RCP<const Basic> get_guard(size_t r, size_t c);

  void accept(SystemVisitor &visitor);

protected:
  // Vector of symbolic state variables.
  std::vector<RCP<const Basic>> states_;

  // Vector of symbolic input variables.
  std::vector<RCP<const Basic>> inputs_;

  // Vector of state equations.
  // Each mode can have several state equations. These are mapped using a tuple.
  std::map<std::tuple<int, int>, RCP<const Basic>> f_;

  // Vector of output equations.
  std::vector<RCP<const Basic>> g_;

  size_t n_modes;

  vector<RCP<const Basic>> guards_
};

} // Controls

#endif /* end of include guard: SYMCTRL_HYBRID_SYSTEM_HPP */
