from setuptools import setup, Extension

module = Extension(
    "pyctrl",
    sources=["py_wrapper.cc"],
    include_dirs=['/usr/local/include'],
    libraries=['libctrl'],
    library_dirs=['/usr/local/lib'],
)

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
