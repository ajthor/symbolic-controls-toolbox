function [t, y] = nlsolver(sys, varargin)
%NLSOLVER Summary of this function goes here
%   Detailed explanation goes here

p = inputParser;
validateTspan = @(tspan) ...
    validateattributes(tspan, {'numeric', 'increasing'}, {'row'});
validateSolver = @(solver) ...
    validateattributes(solver, {'function_handle'}, {'nonempty'});
addRequired(p, 'sys');
addOptional(p, 'tspan', [0 10], validateTspan);
addOptional(p, 'x0', []);
addParameter(p, 'solver', @ode45, validateSolver);
parse(p, sys, varargin{:});

t = sym('t');

nx = cell(size(sys.states));
nx(:) = {'SUBX'};
tx = sym(genvarname(nx, who));
tf = subs(sys.f, sys.states, tx);

Ffun = symfun(formula(tf), [t; tx]);
odefun = matlabFunction(Ffun, 'vars', {t, tx});

tspan = p.Results.tspan;
x0 = reshape(p.Results.x0, [], 1);

solver = p.Results.solver;

[t, y] = feval(solver, odefun, tspan, x0);

end

