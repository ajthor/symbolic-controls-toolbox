#include "random_distribution.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Utility Functions
//
double sample_distribution(RandomNumberDistribution &m,
                           std::random_device &gen) {
  SampleVisitor v(gen);
  m.accept(v);
  return v.get_result();
}

} // Controls
