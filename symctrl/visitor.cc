#include "visitor.hpp"

namespace Controls {

void StateSpace::accept(SystemVisitor &visitor) {
  visitor.visit(*this);
}

void TransferFunction::accept(SystemVisitor &visitor) {
  visitor.visit(*this);
}

void MDP::accept(SystemVisitor &visitor) {
  visitor.visit(*this);
}

void POMDP::accept(SystemVisitor &visitor) {
  visitor.visit(*this);
}

} // Controls
