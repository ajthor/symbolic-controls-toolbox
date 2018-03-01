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

[tx, tu, tf, tg] = varSub(sys);

assume([tx; tu], 'clear');
assume(tu == 0);

% Find equilibrium point.
S = solve(simplify(tf) == 0, tx);

T = sys;
T = subs(T, [tx tu]);
A = subs(T.A, S);
B = subs(T.B, S);
T.f = A*T.states_ + B*T.inputs;

if ~isempty(T.g)
    C = subs(T.C, S);
    D = subs(T.D, S);
    T.g = C*T.states_ + D*T.inputs;
end

T = subs(T, [sys.states; sys.inputs]);
% T.A = subs(subs(subs(T.A, sys.states, tx), S), tx, sys.states);
% T.B = subs(subs(subs(T.B, sys.states, tx), S), tx, sys.states);
% T.C = subs(subs(subs(T.C, sys.states, tx), S), tx, sys.states);
% T.D = subs(subs(subs(T.D, sys.states, tx), S), tx, sys.states);

assume(a);

end

