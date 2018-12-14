#ifndef SYMCTRL_TRANSITION_FUNCTION_HPP
#define SYMCTRL_TRANSITION_FUNCTION_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

// #include "ode.hpp"
// #include "state_space.hpp"
#include "kernel.hpp"
#include "matrix/dense.hpp"

namespace Controls {

class TransitionFunctionVisitor;

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
  virtual ~TransitionFunction() {}

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

  virtual void accept(TransitionFunctionVisitor &visitor) = 0;
};

// ----------------------------------------------------------------------
// TransitionFunction Visitor
//
class TransitionFunctionVisitor {
public:
  virtual void visit(TransitionFunction &m) = 0;
};

// ----------------------------------------------------------------------
// Discrete TransitionFunction
//
class DiscreteTransitionFunction : public TransitionFunction {
private:
  void calc(const std::vector<double> &state,
            const std::vector<double> &input,
            // const std::vector<double> &next_state,
            std::vector<double> &result) {
    //
    // Matrix multiplication.
  }

  Controls::DenseMatrix<double> *transition_matrix_;

public:
  DiscreteTransitionFunction(const size_t nstates,
                             const size_t ninputs) {
    transition_matrix_ = new Controls::DenseMatrix<double>(nstates, nstates);
  }
  ~DiscreteTransitionFunction() {}

  void accept(TransitionFunctionVisitor &visitor) {
    visitor.visit(*this);
  }
};

// ----------------------------------------------------------------------
// Kernelized TransitionFunction
//
template<typename T>
class KernelTransitionFunction : public TransitionFunction {
private:
  void calc(const std::vector<double> &state,
            const std::vector<double> &input,
            // const std::vector<double> &next_state,
            std::vector<double> &result) {
    //
    // Dot product in Hilbert space.
  }

  KernelFunction<T> &kernel_function_;

public:
  KernelTransitionFunction(KernelFunction<T> &K) : kernel_function_(K) {}
  ~KernelTransitionFunction() {}

  void accept(TransitionFunctionVisitor &visitor) {
    visitor.visit(*this);
  }
};

} // Controls

#endif /* end of include guard: SYMCTRL_TRANSITION_FUNCTION_HPP */
