#ifndef SYMCTRL_FUNCTION_HPP
#define SYMCTRL_FUNCTION_HPP

#include <functional>
#include <vector>

namespace Controls {

// ----------------------------------------------------------------------
// Function Class
//
template<typename ...Args>
class Function {
public:
  virtual void eval(Args... args) = 0;
};

// ----------------------------------------------------------------------
// BaseFunction Class
//
template<typename Derived, typename ...Args>
class BaseFunction : public Function<Args...> {
public:
  using Function<Args...>::Function;

  void eval(Args... args) {
    static_cast<Derived *>(this)->eval(args...);
  }
};

// ----------------------------------------------------------------------
// LambdaFunction Class
//
template<typename Fun, typename ...Args>
class LambdaFunction : public BaseFunction<LambdaFunction<Fun, Args...>, Args...> {
private:
  std::function<void(Args...)> f_;

public:
  LambdaFunction(Fun f) : f_(f) {}
  ~LambdaFunction() {}

  void eval(Args... args) {
    f_(args...);
  }
};

template<typename Fun, typename ...Args>
inline Function<Args...> *make_lambda(Fun f, Args...) {
  return new LambdaFunction<Fun, Args...>(f);
}

} // Controls

#endif /* end of include guard: SYMCTRL_FUNCTION_HPP */
