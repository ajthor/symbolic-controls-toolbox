// ---------------------------------------------------------------------------
// Python Wrapper API Interface
//
#ifndef PYTHON_PY_WRAPPER_HPP
#define PYTHON_PY_WRAPPER_HPP

#include "Python.h"

#include "libctrl/c_wrapper.hpp"

#ifdef __cplusplus
extern "C" {
#endif

static PyObject* pyctrl_symss(PyObject* self, PyObject* args);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: PYTHON_PY_WRAPPER_HPP */
