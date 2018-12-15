#ifndef SYMCTRL_TRANSITION_FUNCTION_HPP
#define SYMCTRL_TRANSITION_FUNCTION_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

#include "kernel.hpp"
#include "matrix/dense.hpp"
#include "function.hpp"

typedef Controls::Function<const std::vector<double> &,
                           const std::vector<double> &,
                           std::vector<double> &> transition_function;
//

namespace Controls {

// ----------------------------------------------------------------------
// TransitionFunction
//
class TransitionFunction :
public Controls::BaseFunction<TransitionFunction,
                              const std::vector<double> &,
                              const std::vector<double> &,
                              std::vector<double> &> {
public:
  virtual void eval(const std::vector<double> &state,
                    const std::vector<double> &input,
                    std::vector<double> &result) = 0;
};

template<typename Fun>
inline transition_function *make_transition_function(Fun f) {
  return new Controls::LambdaFunction<Fun,
                                      const std::vector<double> &,
                                      const std::vector<double> &,
                                      std::vector<double> &>(f);
}
//

template<typename T>
inline bool is_a_transition_function(T &b) {
    return dynamic_cast<transition_function *>(&b) != nullptr;
}

// ----------------------------------------------------------------------
// Discrete TransitionFunction
//
class DiscreteTransitionFunction : public TransitionFunction {
private:
  Controls::DenseMatrix<double> *transition_matrix_;

public:
  DiscreteTransitionFunction(const size_t nstates,
                             const size_t ninputs) {
    transition_matrix_ = new Controls::DenseMatrix<double>(nstates, nstates);
  }
  ~DiscreteTransitionFunction() {}

  void eval(const std::vector<double> &state,
            const std::vector<double> &input,
            std::vector<double> &result) {
    //
    // Matrix multiplication.
  }
};

// ----------------------------------------------------------------------
// Kernelized TransitionFunction
//
template<typename T>
class KernelTransitionFunction : public TransitionFunction {
private:
  KernelFunction<T> &kernel_function_;

public:
  KernelTransitionFunction(KernelFunction<T> &K) : kernel_function_(K) {}
  ~KernelTransitionFunction() {}

  void eval(const std::vector<double> &state,
            const std::vector<double> &input,
            std::vector<double> &result) {
    //
    // Dot product in Hilbert space.
  }
};

} // Controls

#endif /* end of include guard: SYMCTRL_TRANSITION_FUNCTION_HPP */
