#ifndef SYMCTRL_MATH_FUNCTOR_FUNCTOR_HPP
#define SYMCTRL_MATH_FUNCTOR_FUNCTOR_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// BaseFunctor Class
//
template<typename R = void, typename ...Args>
class BaseFunctor {
public:
  virtual R eval(Args... args) = 0;
  virtual R operator()(Args... args) = 0;
};

// ----------------------------------------------------------------------
// Functor Class
//
template<typename DT, typename R = void, typename ...Args>
class Functor : public BaseFunctor<R, Args...> {
public:
  using BaseFunctor<R, Args...>::BaseFunctor;

  inline DT &operator~() {
    return *static_cast<DT *>(this);
  }

  inline const DT &operator~() const {
    return *static_cast<const DT *>(this);
  }

  inline R eval(Args... args) {
    return this->operator~().eval(args...);
  }

  inline R operator()(Args... args) {
    return eval(args...);
  }
};

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_FUNCTOR_FUNCTOR_HPP */
