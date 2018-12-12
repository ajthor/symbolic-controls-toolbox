#ifndef SYMCTRL_CANONICAL_HPP
#define SYMCTRL_CANONICAL_HPP

#include "visitor.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Controllable Canonical Form
//
class ControllableFormVisitor : public SystemVisitor {
private:

public:
  ControllableFormVisitor() {}
  ~ControllableFormVisitor() {}

  void visit(StateSpace &m);
  void visit(System &m) {};
};

// ----------------------------------------------------------------------
// Observable Canonical Form
//
class ObservableFormVisitor : public SystemVisitor {
private:

public:
  ObservableFormVisitor() {}
  ~ObservableFormVisitor() {}

  void visit(StateSpace &m);
  void visit(System &m) {};
};

// ----------------------------------------------------------------------
// Jordan Canonical Form
//
class JordanFormVisitor : public SystemVisitor {
private:

public:
  JordanFormVisitor() {}
  ~JordanFormVisitor() {}

  void visit(StateSpace &m);
  void visit(System &m) {};
};


void ctrb_form(StateSpace &m) {
  ControllableFormVisitor s;
  m.accept(s);
}

void obsv_form(StateSpace &m) {
  ObservableFormVisitor s;
  m.accept(s);
}

void jordan_form(StateSpace &m) {
  JordanFormVisitor s;
  m.accept(s);
}

} // Controls

#endif /* end of include guard: SYMCTRL_CANONICAL_HPP */
