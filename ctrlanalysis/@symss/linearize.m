function T = linearize(sys, varargin)
%LINEARIZE Linearize a system around an equilibrium point.
%
%   T = LINEARIZE(sys) linearizes a system around an equilibrium point. If
%   no point is specified, the system is linearized around f(x) = 0.
%
%   T = LINEARIZE(sys, eq) linearizes a system around the equilibrium point
%   defined by eq. For instance, T = LINEARIZE(sys, [x1(0) x2(0)]).

p = inputParser;
validateEQ = @(EQ) ...
    validateattributes(EQ, {'sym', 'numeric', 'cell'}, ...
                           {'size', size([sys.states; sys.inputs])});
addRequired(p, 'sys');
addOptional(p, 'eq', zeros(size([sys.states; sys.inputs])), validateEQ);
parse(p, sys, varargin{:});

eq = p.Results.eq;
if iscell(eq)
    eq = cell2sym(eq);
end

[A, B, C, D] = getabcd(sys);
M = cellfun(@(X) {subs(X, [sys.states; sys.inputs], eq)}, {A, B, C, D});

T = sys;
T.f = M{1}*T.states;
T.g = M{3}*T.states;

if ~isempty(B)
     T.f = T.f + M{2}*T.inputs;
     T.g = T.g + M{4}*T.inputs;
end

end
