// ----------------------------------------------------------------------
// Matlab Wrapper API Function Definitions
//

#include "matlab_wrapper.hpp"

#include "libctrl/state_space.hpp"
#include "libctrl/mdp.hpp"

extern "C" {

struct StateSpace_C {
  Controls::StateSpace m;
};

StateSpace_C* statespace_new() {
  return new StateSpace_C;
}

void statespace_free(StateSpace_C* obj) {
  delete obj;
}

struct MDP_C {
  Controls::MDP m;
};

MDP_C* mdp_new() {
  return new MDP_C;
}

void mdp_free(MDP_C* obj) {
  delete obj;
}

void mdp_set_num_states(MDP_C* obj, int arg) {
  obj->m.set_num_states(arg);
}

void mdp_set_num_inputs(MDP_C* obj, int arg) {
  obj->m.set_num_inputs(arg);
}

void mdp_set_gamma(MDP_C* obj, double arg) {
  obj->m.set_gamma(arg);
}

int mdp_get_num_states(MDP_C* obj) {
  return obj->m.get_num_states();
}

int mdp_get_num_inputs(MDP_C* obj) {
  return obj->m.get_num_inputs();
}

double mdp_get_gamma(MDP_C* obj) {
  return obj->m.get_gamma();
}


} // C

// // void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
// //
// // }
//
// void operator()(ArgumentList outputs, ArgumentList inputs) {
//  checkArguments(outputs, inputs);
//
//  // outputs[0] =
// }
//
// void checkArguments(ArgumentList outputs, ArgumentList inputs) {
//
//   if (outputs.size() > 1) {
//     matlabPtr->feval(convertUTF8StringToUTF16String("error"),
//       0,
//       std::vector<Array>({factory.createScalar("Too many outputs.")}));
//   }
// }
