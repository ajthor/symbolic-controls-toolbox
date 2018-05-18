#include "transfer_function.hpp"

using Controls::TransferFunction;

namespace Controls {

TransferFunction::TransferFunction() {}

TransferFunction::~TransferFunction() {}

void TransferFunction::set_num(const std::vector<RCP<const Basic>> &arg) {
  num_ = arg;
}

void TransferFunction::set_den(const std::vector<RCP<const Basic>> &arg) {
  den_ = arg;
}

std::vector<RCP<const Basic>> TransferFunction::get_num() {
  return num_;
}

std::vector<RCP<const Basic>> TransferFunction::get_den() {
  return den_;
}

} // Controls
