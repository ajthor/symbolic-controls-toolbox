from libcpp.vector cimport vector
from symengine cimport (RCP, pair, map_basic_basic, umap_int_basic,
    umap_int_basic_iterator, umap_basic_num, umap_basic_num_iterator,
    rcp_const_basic, std_pair_short_rcp_const_basic,
    rcp_const_seriescoeffinterface)

cdef extern from "models/state_space.h" namespace "Controls":
    cdef cppclass Rectangle:
        vector[RCP[symengine.Symbol]] states_
        vector[RCP[symengine.Symbol]] inputs_
        vector[RCP[symengine.Symbol]] f_
        vector[RCP[symengine.Symbol]] g_
