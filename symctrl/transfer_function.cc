#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>
#include <symengine/subs.h>

#include "transfer_function.hpp"

using SymEngine::Basic;
using SymEngine::RCP;

namespace Controls {

TransferFunction::TransferFunction() {}
// TransferFunction::TransferFunction(RCP<const Basic> arg) : var_(arg) {};
TransferFunction::~TransferFunction() {}

void
TransferFunction::set_var(const RCP<const Basic> arg) {
  var_ = arg;
}
RCP<const Basic> TransferFunction::get_var() const {
  return var_;
}

void
TransferFunction::add_num(const RCP<const Basic> arg) {
  nums_.push_back(arg);
}
void
TransferFunction::set_num(size_t n,
                          const RCP<const Basic> arg) {
  nums_.at(n) = arg;
}
RCP<const Basic> TransferFunction::get_num(size_t n) const {
  return nums_.at(n);
}
size_t TransferFunction::get_num_nums() const {
  return nums_.size();
}

void
TransferFunction::add_den(const RCP<const Basic> arg) {
  dens_.push_back(arg);
}
void
TransferFunction::set_den(size_t n,
                          const RCP<const Basic> arg) {
  dens_.at(n) = arg;
}
RCP<const Basic> TransferFunction::get_den(size_t n) const {
  return dens_.at(n);
}
size_t TransferFunction::get_num_dens() const {
  return dens_.size();
}

} // Controls
