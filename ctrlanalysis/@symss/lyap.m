function varargout = lyap(sys, varargin)
%LYAP Compute the lyapunov equation of a system.
%   
%   V = LYAP(sys)
%   V = LYAP(sys, Q)
% 
%   To find the Lyapunov equation, we solve P*A + A.'*P == -Q.
% 
%   [V, dV] = LYAP(sys, Q)

linsys = linearize(sys);
A = linsys.A;
% A = subs(A, sys.states, zeros(size(sys.states)));

if nargin < 2
    Q = eye(size(A), 'like', A);
else
    Q = varargin{1};
    if ~isequal(size(A), size(Q))
        error('Invalid matrix dimensions.');
    end
end

P = sym('p', size(A));
expr = A.'*P + P*A == -Q;
S = solve(expr, P);

p = subs(P, S);
if isempty(p)
    error('Could not find a solution to the Lyapunov equation.');
else
    V = sys.states.'*p*sys.states;
    varargout{1} = V;

    if nargout == 2
        [tx, tu, tf, ~] = varsub(sys);
        tv = subs(V, [sys.states; sys.inputs], [tx; tu]);
        dV = gradient(tv, tx).'*tf.';
        dV = subs(dV, [tx; tu], [sys.states; sys.inputs]);
        varargout{2} = dV;
    end
end

end

