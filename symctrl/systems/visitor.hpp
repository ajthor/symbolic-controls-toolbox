#ifndef SYMCTRL_SYSTEMS_VISITOR_HPP
#define SYMCTRL_SYSTEMS_VISITOR_HPP

#include <symctrl/systems/mdp.hpp>
#include <symctrl/systems/state_space.hpp>
#include <symctrl/systems/transfer_function.hpp>

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
template<typename Derived, typename Base = Visitor>
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

// ----------------------------------------------------------------------
// System Accept Function Definitions
//
#define SYMCTRL_SYSTEM_ACCEPT(Class) \
inline void Class::accept(Visitor &visitor) { \
  visitor.visit(*this); \
}
SYMCTRL_SYSTEM_ENUM(SYMCTRL_SYSTEM_ACCEPT)
#undef SYMCTRL_SYSTEM_ACCEPT

} // Controls

#endif // SYMCTRL_SYSTEMS_VISITOR_HPP
