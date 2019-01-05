#ifndef SYMCTRL_SYSTEM_HPP
#define SYMCTRL_SYSTEM_HPP

namespace Controls {

class Visitor;

// ----------------------------------------------------------------------
// BaseSystem Class
//
class BaseSystem {
public:
  virtual ~BaseSystem() {}
  
  virtual void accept(Visitor &visitor) = 0;
};

// ----------------------------------------------------------------------
// System Class
//
template<typename DT>
class System : BaseSystem {
public:
  inline DT &operator~() {
    return *static_cast<DT *>(this);
  }
  inline const DT &operator~() const {
    return *static_cast<const DT *>(this);
  }
};

} // Controls

#endif // SYMCTRL_SYSTEM_HPP
