#ifndef SYMCTRL_MATH_MATRIX_STATIC_STATIC_HPP
#define SYMCTRL_MATH_MATRIX_STATIC_STATIC_HPP

#include <vector>

#include <symctrl/math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// StaticMatrix
//
template<typename T, size_t N, size_t M>
class StaticMatrix : public Matrix<StaticMatrix<T, N, M>> {
private:
  const std::vector<T> v_;

public:
  explicit inline StaticMatrix(const std::vector<T> v);

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline typename std::vector<T>::iterator begin();
  inline typename std::vector<T>::iterator end();
  inline typename std::vector<T>::const_iterator begin() const;
  inline typename std::vector<T>::const_iterator end() const;
  inline typename std::vector<T>::const_iterator cbegin() const;
  inline typename std::vector<T>::const_iterator cend() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline std::vector<T> as_vec() const;

  inline T &operator[](const size_t pos);
  inline const T &operator[](const size_t pos) const;

  inline T &operator()(const size_t row, const size_t col);
  inline const T &operator()(const size_t row, const size_t col) const;
};

template<typename T, size_t N, size_t M>
inline StaticMatrix<T, N, M>::StaticMatrix(const std::vector<T> v) :
                                           v_(v) {
  //
  SYMCTRL_ASSERT(v.size() == N*M);
}

template<typename T, size_t N, size_t M>
inline size_t StaticMatrix<T, N, M>::size() const {
  return N*M;
}

template<typename T, size_t N, size_t M>
inline size_t StaticMatrix<T, N, M>::capacity() const {
  return v_.capacity();
}

template<typename T, size_t N, size_t M>
inline bool StaticMatrix<T, N, M>::empty() const {
  return v_.empty();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::iterator
StaticMatrix<T, N, M>::begin() {
  return v_.begin();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::iterator
StaticMatrix<T, N, M>::end() {
  return v_.end();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::const_iterator
StaticMatrix<T, N, M>::begin() const {
  return v_.begin();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::const_iterator
StaticMatrix<T, N, M>::end() const {
  return v_.end();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::const_iterator
StaticMatrix<T, N, M>::cbegin() const {
  return v_.cbegin();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::const_iterator
StaticMatrix<T, N, M>::cend() const {
  return v_.cend();
}

template<typename T, size_t N, size_t M>
inline size_t StaticMatrix<T, N, M>::nrows() const {
  return N;
}

template<typename T, size_t N, size_t M>
inline size_t StaticMatrix<T, N, M>::ncols() const {
  return M;
}

template<typename T, size_t N, size_t M>
inline std::vector<T> StaticMatrix<T, N, M>::as_vec() const {
  return v_;
}

template<typename T, size_t N, size_t M>
inline T &StaticMatrix<T, N, M>::operator[](const size_t pos) {
  return v_[pos];
}

template<typename T, size_t N, size_t M>
inline const T &StaticMatrix<T, N, M>::operator[](const size_t pos) const {
  return v_[pos];
}

template<typename T, size_t N, size_t M>
inline T &StaticMatrix<T, N, M>::operator()(const size_t row,
                                            const size_t col) {
  return v_[row*M + col];
}

template<typename T, size_t N, size_t M>
inline const T &StaticMatrix<T, N, M>::operator()(const size_t row,
                                                  const size_t col) const {
  return v_[row*M + col];
}

// ----------------------------------------------------------------------
// Stream Output
//
// template<typename T, size_t N, size_t M>
// inline auto operator<<(std::ostream& os, const StaticMatrix<T, N, M> &m)
// -> typename std::enable_if<std::is_scalar<T>::value, std::ostream&>::type {
//   typename std::vector<const T>::iterator result;
//   result = std::max_element((~m).begin(), (~m).end());
//   int width = std::to_string(*result).length();
//
//   for(size_t i = 0; i < (~m).nrows(); i++) {
//     os << "| ";
//     for(size_t j = 0; j < (~m).ncols(); j++) {
//       os << std::setw(width) << (~m)[i*(~m).ncols() + j] << " ";
//     }
//
//     if(i == 0) {
//       os << "| [" << (~m).nrows() << " x " << (~m).ncols() << "]" << '\n';
//     }
//     else {
//       os << "|" << '\n';
//     }
//   }
//   return os;
// }

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_STATIC_STATIC_HPP */
