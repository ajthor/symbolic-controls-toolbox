function V = lyap(varargin)
%LYAP Compute the lyapunov equation of a system.
%   
%   V = LYAP(sys)
%   V = LYAP(sys, Q)
% 
%   To find the Lyapunov equation, we solve P*A + A.'*P == -Q.

sys = varargin{1};
A = sys.A;
A = subs(A, sys.states, zeros(size(sys.states)));

if nargin < 2
    Q = eye(size(A), 'like', A);
else
    Q = varargin{2};
end

P = sym('p', size(A));
expr = P*A + A.'*P == -Q;
S = solve(expr, P);

p = subs(P, S);
if isempty(p)
    warning('Could not find a solution to the ARE.');
    V = sym([]);
else
    V = sys.states.'*P*sys.states;
end

end

