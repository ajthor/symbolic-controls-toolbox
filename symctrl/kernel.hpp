#ifndef SYMCTRL_KERNEL_HPP
#define SYMCTRL_KERNEL_HPP

#include <vector>

#include "matrix/dense.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Kernel Function class.
//
// For each function that takes a matrix as a function parameter, the matrix
// should represent data points on every row.
//
// For example:
//
// Data: (1.0, 1.0), (1.2, 2.1), (1.4, 3.6)
// Matrix:
//   [1.0, 1.0]
//   [1.2, 2.1]
//   [1.4, 3.6]
template<typename T>
class KernelFunction {
public:
  virtual void gramian(const std::vector<T> &x,
                       const std::vector<T> &y,
                       DenseMatrix<double> &result) = 0;
  virtual void gramian(const DenseMatrix<T> &x,
                       const DenseMatrix<T> &y,
                       DenseMatrix<double> &result) = 0;
  virtual void gramian(const DenseMatrix<T> &X,
                       DenseMatrix<double> &result) = 0;
};

// ----------------------------------------------------------------------
// Dot Kernel function.
//
template<typename T>
class DotKernel : public KernelFunction<T> {
public:
  DotKernel() {}

  void gramian(const std::vector<T> &x,
               const std::vector<T> &y,
               DenseMatrix<double> &result);
  void gramian(const DenseMatrix<T> &x,
               const DenseMatrix<T> &y,
               DenseMatrix<double> &result);
  void gramian(const DenseMatrix<T> &X,
               DenseMatrix<double> &result);
};

template<typename T>
void DotKernel<T>::gramian(const std::vector<T> &x,
                           const std::vector<T> &y,
                           DenseMatrix<double> &result) {
  //
  size_t i, j;
  for(i = 0; i < x.size(); i++) {
    for(j = 0; j < y.size(); j++) {
      result(i, j) = x[i] * y[j];
    }
  }
}

template<typename T>
void DotKernel<T>::gramian(const DenseMatrix<T> &x,
                           const DenseMatrix<T> &y,
                           DenseMatrix<double> &result) {
  //

}

template<typename T>
void DotKernel<T>::gramian(const DenseMatrix<T> &X,
                           DenseMatrix<double> &result) {
  //

}

// ----------------------------------------------------------------------
// Polynomial Kernel function.
//
template<typename T>
class PolynomialKernel : public KernelFunction<T> {
private:
  T scale_;
  T offset_;
  T degree_;

public:
  PolynomialKernel(const T scale,
                   const T offset,
                   const T degree) :
                   scale_(scale),
                   offset_(offset),
                   degree_(degree) {}

  void gramian(const std::vector<T> &x,
               const std::vector<T> &y,
               DenseMatrix<double> &result);
  void gramian(const DenseMatrix<T> &x,
               const DenseMatrix<T> &y,
               DenseMatrix<double> &result);
  void gramian(const DenseMatrix<T> &X,
               DenseMatrix<double> &result);
};

template<typename T>
void PolynomialKernel<T>::gramian(const std::vector<T> &x,
                                  const std::vector<T> &y,
                                  DenseMatrix<double> &result) {
  //
  size_t i, j;
  for(i = 0; i < x.size(); i++) {
    for(j = 0; j < y.size(); j++) {
      result(i, j) = pow(scale_ * (x[i] * y[j]) + offset_, degree_);
    }
  }
}

template<typename T>
void PolynomialKernel<T>::gramian(const DenseMatrix<T> &x,
                                  const DenseMatrix<T> &y,
                                  DenseMatrix<double> &result) {
  //

}

template<typename T>
void PolynomialKernel<T>::gramian(const DenseMatrix<T> &X,
                                  DenseMatrix<double> &result) {
  //

}

// ----------------------------------------------------------------------
// Gaussian Kernel function.
//
template<typename T>
class GaussianKernel : public KernelFunction<T> {
private:
  T sigma_;

public:
  GaussianKernel(const T sigma) : sigma_(sigma) {}

  void gramian(const std::vector<T> &x,
               const std::vector<T> &y,
               DenseMatrix<double> &result);
  void gramian(const DenseMatrix<T> &x,
               const DenseMatrix<T> &y,
               DenseMatrix<double> &result);
  void gramian(const DenseMatrix<T> &X,
               DenseMatrix<double> &result);
};

template<typename T>
void GaussianKernel<T>::gramian(const std::vector<T> &x,
                                const std::vector<T> &y,
                                DenseMatrix<double> &result) {
  //
  size_t i, j;

  for(i = 0; i < x.size(); i++) {
    for(j = 0; j < y.size(); j++) {
      result(i, j) =
        ::exp((-1*::pow(::fabs(x[i] - y[j]), 2))/(2*::pow(sigma_, 2)));
    }
  }
}

template<typename T>
void GaussianKernel<T>::gramian(const DenseMatrix<T> &x,
                                const DenseMatrix<T> &y,
                                DenseMatrix<double> &result) {
  //
  size_t i, j;
  std::vector<T> x_norm(x.nrows());
  std::vector<T> y_norm(y.nrows());

  for(i = 0; i < x.nrows(); i++) {
    for(j = 0; j < x.ncols(); j++) {
      x_norm[i] += x(i, j) * x(i, j);
    }
  }

  for(i = 0; i < y.nrows(); i++) {
    for(j = 0; j < y.ncols(); j++) {
      y_norm[i] += y(i, j) * y(i, j);
    }
  }

  DenseMatrix<T> M(x.nrows(), y.nrows());
  // M = x * transpose(y);

  // for(i = 0; i < x.nrows(); i++) {
  //   for(j = 0; j < y.nrows(); j++) {
  //     result(i, j) = x(i, j) * y(i, j);
  //     // result(i, j) = x_norm[i] + y_norm[j] - 2*M(i, j);
  //   }
  // }

  // for(i = 0; i < y.ncols(); i++) {
  //   // result()
  // }

  // result(0, 0) = 1;
  // result(0, 1) = 2;
  // result(1, 0) = 2;
  // result(1, 1) = 1;

}

template<typename T>
void GaussianKernel<T>::gramian(const DenseMatrix<T> &X,
                                DenseMatrix<double> &result) {
  //

}

// ----------------------------------------------------------------------
// Kernel multiplication function.
//
template<typename T>
void kernel_mul(const std::vector<T> &x,
                const std::vector<T> &y,
                const std::vector<T> &alpha,
                KernelFunction<T> *K,
                std::vector<double> &result) {
  //
  size_t i, j;
  double sum_;

  DenseMatrix<double> M(x.size(), y.size());
  K->gramian(x, y, M);

  // Perform the matrix multiplication (M * alpha).
  for(i = 0; i < M.nrows(); i++) {
    sum_ = 0;

    for(j = 0; j < M.ncols(); j++) {
      sum_ += M(i, j) * alpha.at(j);
    }

    result.at(i) = sum_;
  }
}

template<typename T>
void kernel_mul(const DenseMatrix<T> &x,
                const DenseMatrix<T> &y,
                const std::vector<T> &alpha,
                KernelFunction<T> *K,
                std::vector<double> &result) {
  //

}

template<typename T>
void kernel_mul(const DenseMatrix<T> &X,
                std::vector<T> alpha,
                KernelFunction<T> *K,
                std::vector<double> &result) {
  //
  size_t i, j;
  T sum_;

  DenseMatrix<T> M(X.nrows(), X.nrows());
  K->gramian(X, M);

  // Perform the matrix multiplication (M * alpha).
  for(i = 0; i < M.nrows(); i++) {
    sum_ = 0;

    for(j = 0; j < M.ncols(); j++) {
      sum_ += M(i, j) * alpha.at(j);
    }

    result.at(i) = sum_;
  }
}

} // Controls

#endif /* end of include guard: SYMCTRL_KERNEL_HPP */
