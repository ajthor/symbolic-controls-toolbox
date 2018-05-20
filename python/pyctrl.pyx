from libcpp.vector cimport vector

cimport symengine
from symengine cimport RCP, map_basic_basic, rcp_const_basic

cdef extern from "libctrl/state_space.hpp" namespace "Controls":
    cdef cppclass StateSpace "Controls::StateSpace":
        StateSpace() except +

        set_states(vector[rcp_const_basic] &a)
        vector[rcp_const_basic] get_states()

cdef class symss:
    cdef StateSpace* cobj
    def __cinit__(self):
        self.cobj = new StateSpace()
    def __dealloc__(self):
        del self.cobj

@property
def states(self):
    return self.cobj.get_states()

@states.setter
def states(self, a):
    self.cobj.set_states(a)
