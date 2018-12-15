#ifndef SYMCTRL_COST_FUNCTION_HPP
#define SYMCTRL_COST_FUNCTION_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

#include "kernel.hpp"
#include "matrix/dense.hpp"
#include "function.hpp"

typedef Controls::Function<const std::vector<double> &,
                           const std::vector<double> &,
                           double &> cost_function;
//

namespace Controls {

// ----------------------------------------------------------------------
// CostFunction
//
class CostFunction :
public Controls::BaseFunction<CostFunction,
                              const std::vector<double> &,
                              const std::vector<double> &,
                              double &> {
public:
  virtual void eval(const std::vector<double> &state,
                    const std::vector<double> &input,
                    double &result) = 0;
};

template<typename Fun>
inline cost_function *make_cost_function(Fun f) {
  return new Controls::LambdaFunction<Fun,
                                      const std::vector<double> &,
                                      const std::vector<double> &,
                                      double &>(f);
}
//

template<typename T>
inline bool is_a_cost_function(T &b) {
    return dynamic_cast<cost_function *>(&b) != nullptr;
}

// ----------------------------------------------------------------------
// Discrete CostFunction
//
class DiscreteCostFunction :
public CostFunction, public Controls::DenseMatrix<double> {
public:
  DiscreteCostFunction(const size_t n_states,
                       const size_t n_inputs) :
                       Controls::DenseMatrix<double>(n_states*n_inputs, 1) {}
  ~DiscreteCostFunction() {}

  void eval(const std::vector<double> &state,
            const std::vector<double> &input,
            double &result) {
    //
    // Hash the state and input vector to come up with a unique identifier.
    // The identifier corresponds to a specific row in the matrix.
    // Return the result.
  }
};

// ----------------------------------------------------------------------
// Kernelized CostFunction
//
class KernelCostFunction : public CostFunction {
private:
  KernelFunction<double> &kernel_function_;

public:
  KernelCostFunction(KernelFunction<double> &K) : kernel_function_(K) {}
  ~KernelCostFunction() {}

  void eval(const std::vector<double> &state,
            const std::vector<double> &input,
            double &result) {
    //
    // Dot product in Hilbert space.
  }
};

} // Controls

#endif /* end of include guard: SYMCTRL_COST_FUNCTION_HPP */
