function T = linearize(sys, varargin)
%LINEARIZE Linearize a system around an equilibrium point.
%
%   T = LINEARIZE(sys) linearizes a system around an equilibrium point. If
%   no point is specified, the system is linearized around f(x) = 0.
%   
%   T = LINEARIZE(sys, eq) linearizes a system around the equilibrium point
%   defined by eq. For instance, T = LINEARIZE(sys, [x1(0) x2(0)]).

a = assumptions;

[tx, tu, ~, ~] = varsub(sys);
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
    C = subs(simplify(T.C), tx, eq);
    D = subs(simplify(T.D), tx, eq);
    T.g = C*T.states + D*T.inputs;
end

T = subs(T, [sys.states; sys.inputs]);

assume([tx; tu], 'clear');
assume(a);

end

