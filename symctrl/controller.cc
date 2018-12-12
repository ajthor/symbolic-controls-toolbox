#include <symengine/subs.h>

#include "controller.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Gain Controller
//
void GainController::visit(StateSpace &s) {
  size_t m = s.get_num_inputs();
  size_t n = s.get_num_f();

  SymEngine::map_basic_basic d;
  // d[key_] = map_;

  size_t i = 0;
  for(i = 0; i < n; i++) {
    s.set_f(i, SymEngine::ssubs(s.get_f(i), d));
  }

  // for(i = 0; i < p; i++) {
  //   s.set_g(i, SymEngine::ssubs(s.get_g(i), d));
  // }
}

} // Controls
