// ----------------------------------------------------------------------
// Python Wrapper API Function Definitions
//
#include "py_wrapper.hpp"

// Function definitions.
PY_WRAPPER_FUNC(symss) {
  const char* name;

  if (!PyArg_ParseTuple(args, "s", &name))
    return NULL;

  printf("Hello %s!\n", name);

  Py_RETURN_NONE;
}

// Python Method Definitions
static PyMethodDef module_methods[] = {
  PY_WRAPPER_DEF(symss)
  {NULL, NULL, 0, NULL}
};

// Python Module Definition
static struct PyModuleDef pyctrlmodule = {
  PyModuleDef_HEAD_INIT,
  "pyctrl",
  NULL,
  -1,
  module_methods
};

// Initialization function.
PyMODINIT_FUNC
PyInit_pyctrl(void) {
  PyObject *m;

  m = PyModule_Create(&pyctrlmodule);

  if (m == NULL)
    return NULL;

  return m;

  // static void *PySpam_API[1];
  //
  //
  //
  // PySpam_API[PySpam_System_NUM] = (void *)PySpam_System;
  // c_api_object = PyCapsule_New((void *)PySpam_API, "spam._C_API", NULL);
  //
  // if (c_api_object != NULL)
  //   PyModule_AddObject(m, "_C_API", c_api_object);
  // return m;
}
