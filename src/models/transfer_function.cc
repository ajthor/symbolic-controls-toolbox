#include "transfer_function.hpp"
#include "transfer_function.h"

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

// ---------------------------------------------------------------------------
// C Wrapper API Function Definitions
//
struct TransferFunction_C {
  TransferFunction m;
};

TransferFunction_C transferfunction_new() {
  return new TransferFunction_C;
}

void transferfunction_free(TransferFunction_C* obj) {
  delete obj;
}
