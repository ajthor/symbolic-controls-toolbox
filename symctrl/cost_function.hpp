#ifndef SYMCTRL_COST_FUNCTION_HPP
#define SYMCTRL_COST_FUNCTION_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

namespace Controls {

// ----------------------------------------------------------------------
// CostFunction
//
class CostFunction {
private:
  virtual void calc(const std::vector<double> &state,
                    const std::vector<double> &input,
                    double *result) = 0;

public:
  CostFunction();
  ~CostFunction();

  void eval(const std::vector<double> &state,
            const std::vector<double> &input,
            double *result) {
    //
    calc(state, input, result);
  }
};

} // Controls

#endif /* end of include guard: SYMCTRL_COST_FUNCTION_HPP */
