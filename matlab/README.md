# Matlab Bindings

## What is this?

The Matlab bindings provide a Matlab toolbox that is designed to implement the
functionality of the Symbolic Controls Library. It uses
[SymEngine](https://github.com/symengine/symengine) as a symbolic backend, and
uses an inter-operability layer to convert between the Symbolic Toolbox in
Matlab and SymEngine on the backend.

## Getting Started
1. [Download](https://github.com/ajthor/symbolic-controls-toolbox/releases) the toolbox from the GitHub repository.
1. Install the toolbox.
1. Enjoy!

## Your First System

```matlab
% Define symbolic variables.
syms x1 x2

% Create a symbolic state space model.
sys = symss;
sys.states = [x1 x2];

% Define state equations.
sys.f(1) = x2;
sys.f(2) = -sin(x1) - x2;

sys.g(1) = x1;

% Simulate the system.
nlsim2(sys, 0, [0 10], {[1 1]});
```

## For Developers

The generated toolbox should be a stand-alone distribution. 
