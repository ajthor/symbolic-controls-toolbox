// ---------------------------------------------------------------------------
// C Wrapper API Interface
//
#ifdef __cplusplus
extern "C" {
#endif

// Wrapper for TransferFunction.
typedef struct TransferFunction_C TransferFunction_C;

TransferFunction_C* transferfunction_new();
void transferfunction_free(TransferFunction_C* obj);

#ifdef __cplusplus
}
#endif
