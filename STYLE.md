# Style Guide for Symbolic Controls Toolbox

## Functions
- All private utility functions should be closest to their calling functions.

### Directory Structure
- All user-facing functions should perform parameter checking unless the function explicitly calls another function.
- Functions that overload controls toolbox functions should be in class folders `@class` or in a namespace folder `+namespace`.
- Group functions by use, and separate class methods to the appropriate use folder.

### Documentation
- All user-facing functions should include documentation.

### Parameter Checking
- Functions with optional parameters, name/value pairs, and variable arguments should always use `inputParser`.
- Functions with only named parameters should only use `validateattributes`.
- Parameters should be 'camelCase'.

## Tests
- Tests should use demo systems when available.
- Tests should exist for every function for at least 3 systems (if applicable).
