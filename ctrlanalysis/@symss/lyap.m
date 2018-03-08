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
S = solve(P*A + A.'*P == -Q, P);

P = subs(P, S);
V = sys.states.'*P*sys.states;

end

