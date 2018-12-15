#ifndef SYMCTRL_VISITOR_HPP
#define SYMCTRL_VISITOR_HPP

#include "mdp.hpp"
#include "state_space.hpp"
#include "transfer_function.hpp"

namespace Controls {

#ifndef SYMCTRL_SYSTEM_ENUM
#define SYMCTRL_SYSTEM_ENUM(MACRO) \
MACRO(StateSpace) \
MACRO(TransferFunction) \
MACRO(MDP) \
MACRO(POMDP)
#endif

// ----------------------------------------------------------------------
// Visitor Class
//
class Visitor {
public:
  #define SYMCTRL_VISITOR_DECL(Class) \
  virtual void visit(Class &m) = 0;
  SYMCTRL_SYSTEM_ENUM(SYMCTRL_VISITOR_DECL)
  #undef SYMCTRL_VISITOR_DECL
};

// ----------------------------------------------------------------------
// SystemVisitor Class
//
template<class Derived, class Base = Visitor>
class SystemVisitor : public Base {
public:
  using Base::Base;

  #define SYMCTRL_SYSTEM_VISITOR_DECL(Class) \
  virtual void visit(Class &m) { \
    static_cast<Derived *>(this)->visit(m); \
  }
  SYMCTRL_SYSTEM_ENUM(SYMCTRL_SYSTEM_VISITOR_DECL)
  #undef SYMCTRL_SYSTEM_VISITOR_DECL
};

} // Controls

#endif /* end of include guard: SYMCTRL_VISITOR_HPP */
