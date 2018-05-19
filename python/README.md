# Python Bindings

## What is this?

The Python bindings are a Python extension module written in C++ that is
designed to implement the functionality of the Symbolic Controls Library. It
uses [SymEngine](https://github.com/symengine/symengine) as a symbolic backend,
making it inter-operable with [SymPy](http://www.sympy.org/en/index.html).

## Getting Started

Build the Symbolic Controls Library.

```shell
cmake .
make
make install
```

Install the python library from the `python` directory.

```shell
python setup.py install
```

## Your First System

```python
import pyctrl

sys = pyctrl.symss()

```

## For Developers

Use the Python/C API interface for specialized functions that are performance-oriented. Otherwise, use the Cython interface to create the C++ class interface functions.
