# Control Models

This folder contains the C++ classes describing the control models used in the library.

The two primary classes are `StateSpace` and `TransferFunction`.


## Lessons Learned

### CMake

Sometimes, CMake will compile the library, but there are still linking errors in the C++ source that need to be resolved. `ldd` doesn't give complete error descriptions, so use `ld` instead.

```shell
> (cd build && cmake .. && make && make install)
> ld <path/to/library.so>
```
