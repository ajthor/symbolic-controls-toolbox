#ifndef SYMCTRL_TRANSITION_FUNCTION_HPP
#define SYMCTRL_TRANSITION_FUNCTION_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

// #include "ode.hpp"
// #include "state_space.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// TransitionFunction
//
class TransitionFunction {
private:
  virtual void calc(const std::vector<double> &state,
                    const std::vector<double> &input,
                    // const std::vector<double> &next_state,
                    std::vector<double> &result) = 0;

public:
  TransitionFunction();
  ~TransitionFunction();

  void eval(const std::vector<double> &state,
            const std::vector<double> &input,
            // const std::vector<double> &next_state,
            std::vector<double> &result) {
    //

    // Ensure x0 and x1 are n elements or have capacity n.
    if(result.capacity() != state.size()) {

    }

    // Compute the transition.
    calc(state, input, result);
  }
};

} // Controls

#endif /* end of include guard: SYMCTRL_TRANSITION_FUNCTION_HPP */
