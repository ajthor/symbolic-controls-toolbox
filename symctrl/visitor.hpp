#ifndef SYMCTRL_VISITOR_HPP
#define SYMCTRL_VISITOR_HPP

// #include "state_space.hpp"
// #include "transfer_function.hpp"

namespace Controls {

class Visitor {
public:
  virtual ~Visitor() {}
};

class SystemVisitor : public Visitor {
public:
  // virtual void visit(StateSpace &s) = 0;
  // virtual void visit(TransferFunction &s) = 0;
};

class RelizationVisitor : public SystemVisitor {
public:
  // virtual void visit(StateSpace &s) = 0;
};

} // Controls

#endif /* end of include guard: SYMCTRL_VISITOR_HPP */
