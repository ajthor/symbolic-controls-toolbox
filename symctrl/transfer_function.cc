#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>
#include <symengine/subs.h>

#include "transfer_function.hpp"

using Controls::TransferFunction;

namespace Controls {

TransferFunction::TransferFunction() {}
// TransferFunction::TransferFunction(SymEngine::RCP<const SymEngine::Basic> arg) : var_(arg) {};
TransferFunction::~TransferFunction() {}

void
TransferFunction::set_var(const SymEngine::RCP<const SymEngine::Basic> arg) {
  var_ = arg;
}
SymEngine::RCP<const SymEngine::Basic> TransferFunction::get_var() {
  return var_;
}

void
TransferFunction::add_num(const SymEngine::RCP<const SymEngine::Basic> arg) {
  nums_.push_back(arg);
}
void
TransferFunction::set_num(size_t n,
                          const SymEngine::RCP<const SymEngine::Basic> arg) {
  nums_.at(n) = arg;
}
SymEngine::RCP<const SymEngine::Basic> TransferFunction::get_num(size_t n) {
  return nums_.at(n);
}
size_t TransferFunction::get_num_nums() {
  return nums_.size();
}

void
TransferFunction::add_den(const SymEngine::RCP<const SymEngine::Basic> arg) {
  dens_.push_back(arg);
}
void
TransferFunction::set_den(size_t n,
                          const SymEngine::RCP<const SymEngine::Basic> arg) {
  dens_.at(n) = arg;
}
SymEngine::RCP<const SymEngine::Basic> TransferFunction::get_den(size_t n) {
  return dens_.at(n);
}
size_t TransferFunction::get_num_dens() {
  return dens_.size();
}


} // Controls
