#include "visitor.hpp"

namespace Controls {

#define SYMCTRL_SYSTEM_ACCEPT(Class) \
void Class::accept(Visitor &visitor) { \
  visitor.visit(*this); \
}
SYMCTRL_SYSTEM_ENUM(SYMCTRL_SYSTEM_ACCEPT)
#undef SYMCTRL_SYSTEM_ACCEPT

} // Controls
