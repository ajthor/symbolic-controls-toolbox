#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_T_SYM_T_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_T_SYM_T_HPP

#include <memory>
#include <string>

#include <typeinfo>

#include <type_traits>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/sym_var/sym_var.hpp>
#include <symctrl/math/symbolic/sym_number/sym_number.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/type_traits/is_numeric.hpp>
#include <symctrl/type_traits/is_string.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_t
//
class sym_t
    : public Symbolic<sym_t> {
public:
  using this_type = sym_t;

  static constexpr bool isNumeric = false;

private:
  class Concept {
  public:
    virtual ~Concept() = default;

    virtual std::string as_str() const = 0;
    virtual hash_t hash() const = 0;

    virtual bool canEvaluate() const = 0;
  };

  template<typename T>
  class Model final
      : public Concept {
  public:
    using type = T;

  private:
    T data_;

  public:
    Model(T m)
        : data_(m) {}

    virtual std::string as_str() const override {
      return data_.as_str();
    }
    virtual hash_t hash() const override {
      return data_.hash();
    }

    virtual bool canEvaluate() const override {
      return data_.canEvaluate();
    }

  private:
    // template<typename DT>
    // friend inline void apply_(Symbolic<DT> &lhs, const Concept &rhs) {
    //   std::cout << "Concept::apply_" << '\n';
    //   std::cout << "lhs type: " << typeid(std::declval<DT>()).name() << '\n';
    //   std::cout << "rhs type: " << typeid(std::declval<T>()).name() << '\n';
    //   apply_(~lhs, static_cast<const Model<T> &>(rhs).data_);
    // }

    // template<typename DT>
    // friend inline void apply_add_(Symbolic<DT> &lhs, const Concept &rhs) {
    //   std::cout << "Concept::apply_add_" << '\n';
    //   std::cout << "lhs type: " << typeid(std::declval<DT>()).name() << '\n';
    //   std::cout << "rhs type: " << typeid(std::declval<T>()).name() << '\n';
    //   apply_add_(~lhs, static_cast<const Model<T> &>(rhs).data_);
    // }
    //
    // template<typename DT>
    // friend inline void apply_mul_(Symbolic<DT> &lhs, const Concept &rhs) {
    //   std::cout << "Concept::apply_mul_" << '\n';
    //   std::cout << "lhs type: " << typeid(std::declval<DT>()).name() << '\n';
    //   std::cout << "rhs type: " << typeid(std::declval<T>()).name() << '\n';
    //   apply_mul_(~lhs, static_cast<const Model<T> &>(rhs).data_);
    // }

    // template<typename DT>
    // friend inline auto eval_add_(const Concept &lhs, const Symbolic<DT> &rhs)
    // -> decltype(std::declval<Model<T>::type>() + std::declval<Symbolic<DT>>()) {
    //   return static_cast<const Model<T> &>(lhs).data_ + rhs;
    // }

    // template<typename DT>
    // friend inline auto eval_add_(const Concept &lhs, const Symbolic<DT> &rhs)
    // -> std::shared_ptr<const Concept> {
    //   SYMCTRL_DEBUG("Concept::eval_add_");
    //   using ReturnType = decltype(std::declval<T>() + std::declval<DT>());
    //
    //   auto result = (static_cast<const Model<T> &>(lhs).data_ + ~rhs);
    //   return std::make_shared<Model<ReturnType>>((result));
    // }

    // template<typename DT>
    // friend inline auto eval_add_(const Concept &lhs, const Symbolic<DT> &rhs)
    // -> std::shared_ptr<const Concept> {
    //   SYMCTRL_DEBUG("Concept::eval_add_");
    //   using ReturnType = decltype(std::declval<T>() + std::declval<DT>());
    //
    //   std::cout << "lhs type: " << typeid(std::declval<T>()).name() << '\n';
    //   std::cout << "rhs type: " << typeid(std::declval<DT>()).name() << '\n';
    //   std::cout << "return type: " << typeid(std::declval<ReturnType>()).name() << '\n';
    //
    //   auto result = (static_cast<const Model<T> &>(lhs).data_ + ~rhs);
    //   std::cout << "result type: " << typeid(result).name() << '\n';
    //
    //   return std::make_shared<Model<ReturnType>>((result));
    //   // return std::make_shared<Model<ReturnType>>((static_cast<const Model<T> &>(lhs).data_ + rhs));
    //
    //   // auto lhs_data_ = static_cast<const Model<T> &>(lhs).data_;
    //   // return std::make_shared<Model<ReturnType>>(lhs_data_ + rhs);
    // }

    // template<typename DT>
    // friend inline void eval_add_(std::shared_ptr<const Concept> &lhs, const Symbolic<DT> &rhs) {
    //   SYMCTRL_DEBUG("Concept::eval_add_");
    //   using ReturnType = decltype(std::declval<T>() + std::declval<DT>());
    //
    //   std::cout << "lhs type: " << typeid(std::declval<T>()).name() << '\n';
    //   std::cout << "rhs type: " << typeid(std::declval<DT>()).name() << '\n';
    //   std::cout << "return type: " << typeid(std::declval<ReturnType>()).name() << '\n';
    //
    //   auto result = (static_cast<const Model<T> &>(*lhs).data_ + ~rhs);
    //   std::cout << "result type: " << typeid(result).name() << '\n';
    //
    //   lhs.reset();
    //   lhs = std::make_shared<Model<ReturnType>>((result));
    // }

    // template<typename DT>
    // friend inline auto eval_mul_(const Concept &lhs, const Symbolic<DT> &rhs)
    // -> std::shared_ptr<const Concept> {
    //   SYMCTRL_DEBUG("Concept::eval_mul_");
    //   using ReturnType = decltype(std::declval<T>() * std::declval<DT>());
    //
    //   auto result = (static_cast<const Model<T> &>(lhs).data_ * ~rhs);
    //   return std::make_shared<Model<ReturnType>>((result));
    // }
  };

  // template<typename DT>
  // friend inline void apply_(Symbolic<DT> &lhs, const Concept &rhs);
  // template<typename DT>
  // friend inline void apply_add_(Symbolic<DT> &lhs, const Concept &rhs);
  // template<typename DT>
  // friend inline void apply_mul_(Symbolic<DT> &lhs, const Concept &rhs);

  // template<typename DT>
  // friend inline auto eval_add_(const Concept &lhs, const Symbolic<DT> &rhs)
  // -> std::shared_ptr<const Concept>;
  // template<typename DT>
  // friend inline void eval_add_(std::shared_ptr<const Concept> &lhs, const Symbolic<DT> &rhs);
  // template<typename DT>
  // friend inline auto eval_add_(const Concept &lhs, const Symbolic<DT> &rhs)
  // -> std::shared_ptr<const Concept>;
  //
  // template<typename DT>
  // friend inline auto eval_mul_(const Concept &lhs, const Symbolic<DT> &rhs)
  // -> std::shared_ptr<const Concept>;

  std::shared_ptr<const Concept> ptr_;

public:
  template<typename T, enable_if_string_t<T, int> = 0>
  explicit inline sym_t(T m);

  template<typename T, enable_if_numeric_t<T, int> = 0>
  inline sym_t(T m);

  template<typename DT>
  inline sym_t(const Symbolic<DT> &m);
  template<typename DT>
  inline sym_t(Symbolic<DT> &&m);

  template<typename DT>
  inline sym_t &operator=(const Symbolic<DT> &rhs);
  template<typename DT>
  inline sym_t &operator=(Symbolic<DT> &&rhs);

  template<typename DT>
  inline void apply(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_add(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline void apply_diff(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline void apply_div(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_mul(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline void apply_neg(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline void apply_pow(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline void apply_sub(const Symbolic<DT> &rhs);

  inline std::string as_str() const;
  inline hash_t hash() const;

  inline bool canEvaluate() const;

private:
  template<typename DT>
  friend inline void apply_(Symbolic<DT> &lhs, const sym_t &rhs) {
    SYMCTRL_DEBUG("sym_t::apply_");
    // apply_(~lhs, *rhs.ptr_);
  }

  template<typename DT>
  friend inline void apply_add_(Symbolic<DT> &lhs, const sym_t &rhs) {
    SYMCTRL_DEBUG("sym_t::apply_add_");
    // apply_add_(~lhs, *rhs.ptr_);
  }

  template<typename DT>
  friend inline void apply_mul_(Symbolic<DT> &lhs, const sym_t &rhs) {
    SYMCTRL_DEBUG("sym_t::apply_mul_");
    // apply_mul_(~lhs, *rhs.ptr_);
  }
};

// ----------------------------------------------------------------------
// sym_t Constructor
//
template<typename T, enable_if_string_t<T, int>>
inline sym_t::sym_t(T m)
    : ptr_(std::make_shared<Model< sym_var >>(std::move(std::string(m)))) {}

template<typename T, enable_if_numeric_t<T, int>>
inline sym_t::sym_t(T m)
    : ptr_(std::make_shared<Model< sym_number<T> >>(std::move(m))) {}

// template<typename DT>
// inline sym_t::sym_t(const Symbolic<DT> &m)
//     : ptr_(std::make_shared<Model<DT>>(~m)) {}
//
// template<typename DT>
// inline sym_t::sym_t(Symbolic<DT> &&m)
//     : ptr_(std::make_shared<Model<DT>>(std::move(~m))) {}

template<typename DT>
inline sym_t::sym_t(const Symbolic<DT> &m) {
  apply_(*this, ~m);
}

template<typename DT>
inline sym_t::sym_t(Symbolic<DT> &&m) {
  apply_(*this, std::move(~m));
}

// ----------------------------------------------------------------------
// sym_t Assignment Operator
//
// template<typename DT>
// inline sym_t &sym_t::operator=(const Symbolic<DT> &rhs) {
//   ptr_.reset();
//   ptr_ = std::make_shared<Model<DT>>(~rhs);
//   return *this;
// }
//
// template<typename DT>
// inline sym_t &sym_t::operator=(Symbolic<DT> &&rhs) {
//   ptr_.reset();
//   ptr_ = std::make_shared<Model<DT>>(std::move(~rhs));
//   return *this;
// }

template<typename DT>
inline sym_t &sym_t::operator=(const Symbolic<DT> &rhs) {
  apply_(*this, ~rhs);
  return *this;
}

template<typename DT>
inline sym_t &sym_t::operator=(Symbolic<DT> &&rhs) {
  apply_(*this, std::move(~rhs));
  return *this;
}

// ----------------------------------------------------------------------
// sym_t Member Function Definitions
//
inline std::string sym_t::as_str() const {
  return ptr_->as_str();
}

inline hash_t sym_t::hash() const {
  return ptr_->hash();
}

inline bool sym_t::canEvaluate() const {
 return ptr_->canEvaluate();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_T_SYM_T_HPP
