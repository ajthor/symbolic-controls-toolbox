#ifndef SYMCTRL_MATH_FUNCTOR_KERNEL_HPP
#define SYMCTRL_MATH_FUNCTOR_KERNEL_HPP

#include <vector>

#include <symctrl/math/functor/functor.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// KernelFunction
//
// For each function that takes a matrix as a function parameter, the
// matrix should represent data points on every row.
//
// For example:
//
// Data: (1.0, 1.0), (1.2, 2.1), (1.4, 3.6)
// Matrix:
//   [1.0, 1.0]
//   [1.2, 2.1]
//   [1.4, 3.6]
class KernelFunction : public Functor<KernelFunction,
                                      double,
                                      const std::vector<double> &,
                                      const std::vector<double> &> {
public:
  virtual double eval(const std::vector<double> &input,
                      const std::vector<double> &output) = 0;
};


// ----------------------------------------------------------------------
// Dot Kernel
//
class DotKernel : public KernelFunction {
public:
  explicit inline DotKernel() {}
  // ~DotKernel() {}

  double eval(const std::vector<double> &x,
                   const std::vector<double> &y);
};

// ----------------------------------------------------------------------
// Polynomial Kernel
//
class PolynomialKernel : public KernelFunction {
private:
  double scale_;
  double offset_;
  int degree_;

public:
  explicit inline PolynomialKernel(const double scale,
                                   const double offset,
                                   const int degree) :
                                   scale_(scale),
                                   offset_(offset),
                                   degree_(degree) {}
  // ~PolynomialKernel() {}

  double eval(const std::vector<double> &x,
                   const std::vector<double> &y);
};

// ----------------------------------------------------------------------
// Gaussian Kernel
//
class GaussianKernel : public KernelFunction {
private:
  double sigma_;

public:
  explicit inline GaussianKernel(const double sigma) :
                                 sigma_(sigma) {}
  // ~GaussianKernel() {}

  double eval(const std::vector<double> &x,
                   const std::vector<double> &y);
};

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_FUNCTOR_KERNEL_HPP */
