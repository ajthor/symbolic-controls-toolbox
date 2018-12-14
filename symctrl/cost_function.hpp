#ifndef SYMCTRL_COST_FUNCTION_HPP
#define SYMCTRL_COST_FUNCTION_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

#include "matrix/dense.hpp"

namespace Controls {

class CostFunctionVisitor;

// ----------------------------------------------------------------------
// CostFunction
//
class CostFunction {
private:
  virtual void calc(const std::vector<double> &state,
                    const std::vector<double> &input,
                    double *result) = 0;

public:
  virtual ~CostFunction() {}

  void eval(const std::vector<double> &state,
            const std::vector<double> &input,
            double *result) {
    //
    calc(state, input, result);
  }

  virtual void accept(CostFunctionVisitor &visitor) = 0;
};

// ----------------------------------------------------------------------
// CostFunction Visitor
//
class CostFunctionVisitor {
public:
  virtual void visit(CostFunction &m) = 0;
};

// ----------------------------------------------------------------------
// Discrete CostFunction
//
class DiscreteCostFunction : public CostFunction {
private:
  void calc(const std::vector<double> &state,
            const std::vector<double> &input,
            double *result) {
    //
    // Matrix multiplication.
  }

  Controls::DenseMatrix<double> *cost_matrix_;

public:
  DiscreteCostFunction(const size_t nstates,
                       const size_t ninputs) {
    cost_matrix_ = new Controls::DenseMatrix<double>(nstates, ninputs);
  }
  ~DiscreteCostFunction() {}

  void accept(CostFunctionVisitor &visitor) {
    visitor.visit(*this);
  }
};

} // Controls

#endif /* end of include guard: SYMCTRL_COST_FUNCTION_HPP */
