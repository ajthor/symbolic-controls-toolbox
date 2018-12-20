#ifndef MATH_MATRIX_EXPR_HPP
#define MATH_MATRIX_EXPR_HPP

#include "matrix.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Expression
//
template<typename T, typename Derived>
class Expression : public Matrix<T, Expression<T, Derived>> {
public:
  // size_t size() const;
  // size_t capacity() const;
  //
  // bool empty() const;
  //
  // typename std::vector<T>::iterator begin();
  // typename std::vector<T>::iterator end();
  // typename std::vector<T>::const_iterator begin() const;
  // typename std::vector<T>::const_iterator end() const;
  // typename std::vector<T>::const_iterator cbegin() const;
  // typename std::vector<T>::const_iterator cend() const;
  //
  // size_t nrows() const;
  // size_t ncols() const;
  //
  // std::vector<T> as_vec() const;
  //
  // virtual T &operator[](const size_t pos) = 0;
  // virtual const T &operator[](const size_t pos) const = 0;
  //
  // void transpose();
};

// template<typename T, typename Derived>
// size_t Expression<T, Derived>::size() const {}
// template<typename T, typename Derived>
// size_t Expression<T, Derived>::capacity() const {}
//
// template<typename T, typename Derived>
// bool Expression<T, Derived>::empty() const {}
//
// template<typename T, typename Derived>
// typename std::vector<T>::iterator Expression<T, Derived>::begin() {}
// template<typename T, typename Derived>
// typename std::vector<T>::iterator Expression<T, Derived>::end() {}
// template<typename T, typename Derived>
// typename std::vector<T>::const_iterator Expression<T, Derived>::begin() const {}
// template<typename T, typename Derived>
// typename std::vector<T>::const_iterator Expression<T, Derived>::end() const {}
// template<typename T, typename Derived>
// typename std::vector<T>::const_iterator Expression<T, Derived>::cbegin() const {}
// template<typename T, typename Derived>
// typename std::vector<T>::const_iterator Expression<T, Derived>::cend() const {}
//
// template<typename T, typename Derived>
// size_t Expression<T, Derived>::nrows() const {}
// template<typename T, typename Derived>
// size_t Expression<T, Derived>::ncols() const {}
//
// template<typename T, typename Derived>
// std::vector<T> Expression<T, Derived>::as_vec() const {}
//
// template<typename T, typename Derived>
// T &Expression<T, Derived>::operator[](const size_t pos) {}
// template<typename T, typename Derived>
// const T &Expression<T, Derived>::operator[](const size_t pos) const {}
//
// template<typename T, typename Derived>
// void Expression<T, Derived>::transpose() {}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_HPP */
