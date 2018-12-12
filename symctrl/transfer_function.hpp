#ifndef SYMCTRL_TRANSFER_FUNCTION_HPP
#define SYMCTRL_TRANSFER_FUNCTION_HPP

#include <vector>
#include <symengine/basic.h>

#include "system.hpp"

using SymEngine::Basic;
using SymEngine::RCP;

namespace Controls {

class TransferFunction : public System {
public:
  TransferFunction();
  TransferFunction(const RCP<const Basic> arg) : var_(arg) {};
  ~TransferFunction();

  void set_var(const RCP<const Basic> arg);
  RCP<const Basic> get_var() const;

  void add_num(const RCP<const Basic> arg);
  void set_num(const size_t n, const RCP<const Basic> arg);
  RCP<const Basic> get_num(const size_t n) const;
  // void remove_num(size_t n);
  size_t get_num_nums() const;

  void add_den(const RCP<const Basic> arg);
  void set_den(const size_t n, const RCP<const Basic> arg);
  RCP<const Basic> get_den(const size_t n) const;
  // void remove_den(size_t n);
  size_t get_num_dens() const;

  void accept(Visitor &visitor);

private:
  RCP<const Basic> var_;

  SymEngine::vec_basic nums_;
  SymEngine::vec_basic dens_;
};

void transferfunction_poles();
void transferfunction_zeros();

void minimal_realization();

} // Controls

#endif /* end of include guard: SYMCTRL_TRANSFER_FUNCTION_HPP */
