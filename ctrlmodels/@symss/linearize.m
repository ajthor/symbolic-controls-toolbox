function T = linearize(sys, varargin)
%LINEARIZE Linearize a system around an equilibrium point.
%
%   Detailed explanation goes here 
%   
%   The input parameter 'eqns' should be a system of symbolic functions 
%   organized into a cell array. Typically, 

% p = inputParser;
% validateSys = @(sys) isa(sys, 'symss');
% addRequired(p, 'sys', validateSys);
% addParameter(p, 'assumptions', {sys.states == 0, sys.inputs == 0});
% parse(p, sys, varargin{:});

a = assumptions;
% assume(p.Results.assumptions{:});

[tx, tu, tf, ~] = varSub(sys);

assume([tx; tu], 'clear');

T = sys;
T = subs(T, [tx; tu]);

% Set equilibrium point.
if nargin > 1
    eq = reshape([varargin{:}], [], 1);
else
    eq = zeros(size(tx));
end

assume(tx == eq);
assume(tu == 0);
% Substitute the equilibrium point in for variables.
A = subs(simplify(T.A), tx, eq);
B = subs(simplify(T.B), tx, eq);
% Compute linearized state equations.
T.f = A*T.states + B*T.inputs;

if ~isempty(T.g)
    C = simplify(T.C);
    D = simplify(T.D);
    T.g = C*T.states + D*T.inputs;
end

T = subs(T, [sys.states; sys.inputs]);

% T.A = subs(subs(subs(T.A, sys.states, tx), S), tx, sys.states);
% T.B = subs(subs(subs(T.B, sys.states, tx), S), tx, sys.states);
% T.C = subs(subs(subs(T.C, sys.states, tx), S), tx, sys.states);
% T.D = subs(subs(subs(T.D, sys.states, tx), S), tx, sys.states);

assume([tx; tu], 'clear');
assume(a);

end

