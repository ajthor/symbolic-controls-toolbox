import os
from setuptools import setup, Extension

# Check if the USE_SETUPTOOLS environment variable is set.
use_cython = True
use_setuptools = os.getenv('USE_SETUPTOOLS')

if use_setuptools is not None:
    if use_setuptools.lower() == 'true':
        use_cython = False

# Load Cython.
if use_cython:
    try:
        from Cython.Build import cythonize
    except ImportError:
        use_cython = False

if not use_cython:
    # If the USE_SETUPTOOLS flag is set, or if Cython is not installed, install
    # the library using setuptools as a Python/C extension.
    module = Extension(
        "pyctrl",
        sources=["py_wrapper.cc"],
        include_dirs=['/usr/local/include'],
    )
else:
    module = cythonize(Extension(
        'pyctrl',
        sources=['py_wrapper.pyx'],
        include_dirs=['/usr/local/include'],
        extra_compile_args=['-std=c++11'],
        language='c++',
    ))

long_description = '''
The Symbolic Controls Toolbox is a C++ symbolic library for working with control systems licensed under the MIT general license.
See https://github.com/ajthor/symbolic-controls-toolbox for more information.
'''

setup(
    name="pyctrl",
    version="0.1.0",
    description="Python library for control systems.",
    long_description=long_description,
    author="Adam Thorpe",
    license="MIT",
    url="https://github.com/ajthor/symbolic-controls-toolbox",
    keywords="control systems hybrid nonlinear mdp",
    ext_modules=[module],
)
