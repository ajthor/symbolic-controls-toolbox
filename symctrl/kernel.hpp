#ifndef SYMCTRL_KERNEL_HPP
#define SYMCTRL_KERNEL_HPP

#include <vector>

#include "matrix/dense.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Kernel Function class.
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
template<typename T>
class KernelFunction {
public:
  virtual void gramian(const std::vector<T> &x,
                       const std::vector<T> &y,
                       Controls::DenseMatrix<double> &result) = 0;
  virtual void gramian(const Controls::DenseMatrix<T> &X,
                       const Controls::DenseMatrix<T> &Y,
                       Controls::DenseMatrix<double> &result) = 0;
  virtual void gramian(const Controls::DenseMatrix<T> &X,
                       Controls::DenseMatrix<double> &result) = 0;
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
               Controls::DenseMatrix<double> &result);
  void gramian(const Controls::DenseMatrix<T> &X,
               const Controls::DenseMatrix<T> &Y,
               Controls::DenseMatrix<double> &result);
  void gramian(const Controls::DenseMatrix<T> &X,
               Controls::DenseMatrix<double> &result);
};

template<typename T>
void DotKernel<T>::gramian(const std::vector<T> &x,
                           const std::vector<T> &y,
                           Controls::DenseMatrix<double> &result) {
  //
#pragma omp parallel for
  for(size_t i = 0; i < x.size(); i++) {
    for(size_t j = 0; j < y.size(); j++) {
      result(i, j) = x[i] * y[j];
    }
  }
}

template<typename T>
void DotKernel<T>::gramian(const Controls::DenseMatrix<T> &X,
                           const Controls::DenseMatrix<T> &Y,
                           Controls::DenseMatrix<double> &result) {
  //

}

template<typename T>
void DotKernel<T>::gramian(const Controls::DenseMatrix<T> &X,
                           Controls::DenseMatrix<double> &result) {
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
               Controls::DenseMatrix<double> &result);
  void gramian(const Controls::DenseMatrix<T> &X,
               const Controls::DenseMatrix<T> &Y,
               Controls::DenseMatrix<double> &result);
  void gramian(const Controls::DenseMatrix<T> &X,
               Controls::DenseMatrix<double> &result);
};

template<typename T>
void PolynomialKernel<T>::gramian(const std::vector<T> &x,
                                  const std::vector<T> &y,
                                  Controls::DenseMatrix<double> &result) {
  //
#pragma omp parallel for
  for(size_t i = 0; i < x.size(); i++) {
    for(size_t j = 0; j < y.size(); j++) {
      result(i, j) = pow(scale_ * (x[i] * y[j]) + offset_, degree_);
    }
  }
}

template<typename T>
void PolynomialKernel<T>::gramian(const Controls::DenseMatrix<T> &X,
                                  const Controls::DenseMatrix<T> &Y,
                                  Controls::DenseMatrix<double> &result) {
  //

}

template<typename T>
void PolynomialKernel<T>::gramian(const Controls::DenseMatrix<T> &X,
                                  Controls::DenseMatrix<double> &result) {
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
               Controls::DenseMatrix<double> &result);
  void gramian(const Controls::DenseMatrix<T> &X,
               const Controls::DenseMatrix<T> &Y,
               Controls::DenseMatrix<double> &result);
  void gramian(const Controls::DenseMatrix<T> &X,
               Controls::DenseMatrix<double> &result);
};

template<typename T>
void GaussianKernel<T>::gramian(const std::vector<T> &x,
                                const std::vector<T> &y,
                                Controls::DenseMatrix<double> &result) {
  //
#pragma omp parallel for
  for(size_t i = 0; i < x.size(); i++) {
    for(size_t j = 0; j < y.size(); j++) {
      result(i, j) =
        ::exp((-1*::pow(::fabs(x[i] - y[j]), 2))/(2*::pow(sigma_, 2)));
    }
  }
}

template<typename T>
void GaussianKernel<T>::gramian(const Controls::DenseMatrix<T> &X,
                                const Controls::DenseMatrix<T> &Y,
                                Controls::DenseMatrix<double> &result) {
  //
  size_t i, j, k;

  // Compute the norm of each row.
  std::vector<T> x_norm(X.nrows(), 0);
  std::vector<T> y_norm(Y.nrows(), 0);

  for(i = 0; i < X.nrows(); i++) {
    for(j = 0; j < X.ncols(); j++) {
      x_norm[i] += X(i, j) * X(i, j);
    }
  }

  for(i = 0; i < Y.nrows(); i++) {
    for(j = 0; j < Y.ncols(); j++) {
      y_norm[i] += Y(i, j) * Y(i, j);
    }
  }

  // Initialize the matrix to hold the intermediate result (X * Y').
  Controls::DenseMatrix<double> M(X.nrows(), Y.nrows());
  zeros(M);

  // Compute (X * Y').
  for(i = 0; i < X.nrows(); i++) {
    for(j = 0; j < Y.nrows(); j++) {
      for(k = 0; k < X.ncols(); k++) {
        M(i, j) += X(i, k) * Y(j, k);
      }
    }
  }

  // Compute the Gramian.
  for(i = 0; i < M.nrows(); i++) {
    for(j = 0; j < M.ncols(); j++) {
      result(i, j) =
        ::exp(-1*(x_norm[i] + y_norm[j] - 2*M(i, j))/(2*::pow(sigma_, 2)));
    }
  }
}

template<typename T>
void GaussianKernel<T>::gramian(const Controls::DenseMatrix<T> &X,
                                Controls::DenseMatrix<double> &result) {
  //

}

// ----------------------------------------------------------------------
// Kernel coefficient vector function.
//
template<typename T>
void kernel_coefficient_vector(const Controls::DenseMatrix<double> &K,
                               const double lambda,
                               std::vector<double> &alpha) {
  //

  size_t m = K.nrows();

  // Calculate K + (lambda * m * I)
  for(size_t i = 0; i < m; i++) {
    // K(i, i) += lambda * m;
  }

  // Calculate W = (K + (lambda * m * I))^-1
  Controls::DenseMatrix<double> W(m, m);

}

// ----------------------------------------------------------------------
// Kernel estimate function.
//
template<typename T>
void kernel_estimate(const std::vector<T> &x,
                     const std::vector<T> &y,
                     const std::vector<double> &alpha,
                     KernelFunction<T> *K,
                     std::vector<double> &result) {
  //
  double sum_;

  Controls::DenseMatrix<double> M(x.size(), y.size());
  K->gramian(x, y, M);

  // Perform the matrix multiplication (M * alpha).
#pragma omp parallel for
  for(size_t i = 0; i < M.nrows(); i++) {
    sum_ = 0;

    for(size_t j = 0; j < M.ncols(); j++) {
      sum_ += M(i, j) * alpha.at(j);
    }

    result.at(i) = sum_;
  }
}

template<typename T>
void kernel_estimate(const Controls::DenseMatrix<T> &X,
                     const Controls::DenseMatrix<T> &Y,
                     const std::vector<double> &alpha,
                     KernelFunction<T> *K,
                     std::vector<double> &result) {
  //
  double sum_;

  Controls::DenseMatrix<double> M(X.nrows(), Y.nrows());
  K->gramian(X, Y, M);

  // Perform the matrix multiplication (M * alpha).
#pragma omp parallel for
  for(size_t i = 0; i < M.nrows(); i++) {
    sum_ = 0;

    for(size_t j = 0; j < M.ncols(); j++) {
      sum_ += M(i, j) * alpha.at(j);
    }

    result.at(i) = sum_;
  }
}

template<typename T>
void kernel_estimate(const Controls::DenseMatrix<T> &X,
                     std::vector<double> &alpha,
                     KernelFunction<T> *K,
                     std::vector<double> &result) {
  //
  size_t i, j;
  T sum_;

  Controls::DenseMatrix<T> M(X.nrows(), X.nrows());
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
