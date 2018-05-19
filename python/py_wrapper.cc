// ----------------------------------------------------------------------
// Python Wrapper API Function Definitions
//
#include "py_wrapper.hpp"

#ifndef POS_PARAM
#define POS_PARAM METH_VARARGS
#endif

#ifndef KWD_PARAM
#define KWD_PARAM METH_VARARGS | METH_KEYWORDS
#endif

#ifndef PY_WRAPPER_FUNC
#define PY_WRAPPER_FUNC(name) \
static PyObject* pyctrl_##name(PyObject* self, PyObject* args)
#endif

#ifndef PY_WRAPPER_DESC
#define PY_WRAPPER_DESC(name) \
static char pyctrl_##name##_desc[]
#endif

#ifndef PY_WRAPPER_DEF
#define PY_WRAPPER_DEF(name) \
  {#name, pyctrl_##name, POS_PARAM, pyctrl_##name##_desc},
#endif

// Function descriptions.
PY_WRAPPER_DESC(symss) = "Create a state-space model.";

// Function definitions.
PY_WRAPPER_FUNC(symss) {
  const char* name;

  if (!PyArg_ParseTuple(args, "s", &name))
    return NULL;

  printf("Hello %s!\n", name);

  Py_RETURN_NONE;
}

// PyMethodDef
static PyMethodDef module_methods[] = {
  PY_WRAPPER_DEF(symss)
  {NULL, NULL, 0, NULL}
};

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
  return PyModule_Create(&pyctrlmodule);

  // (void) Py_InitModule("pyctrl", module_methods);

  // PyObject *m;
  // static void *PySpam_API[1];
  //
  // m = PyModule_Create(&spammodule);
  //
  // if (m == NULL)
  //   return NULL;
  //
  // PySpam_API[PySpam_System_NUM] = (void *)PySpam_System;
  // c_api_object = PyCapsule_New((void *)PySpam_API, "spam._C_API", NULL);
  //
  // if (c_api_object != NULL)
  //   PyModule_AddObject(m, "_C_API", c_api_object);
  // return m;
}
