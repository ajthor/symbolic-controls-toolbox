// ---------------------------------------------------------------------------
// C Wrapper API Interface
//
#ifdef __cplusplus
extern "C" {
#endif

// Wrapper for StateSpace.
typedef struct StateSpace_C StateSpace_C;

StateSpace_C* statespace_new();
void statespace_free(StateSpace_C* obj);

void statespace_set_states(StateSpace_C* obj, );

#ifdef __cplusplus
}
#endif
