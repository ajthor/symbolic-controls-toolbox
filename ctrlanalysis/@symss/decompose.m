function varargout = decompose(sys)
%DECOMPOSE Compute the Kalman decomposition of a state-space realization.
% 
%   sys = DECOMPOSE(sys) computes the Kalman decomposition of a state-space
%   realization.
%   
%   [sys, n] = DECOMPOSE(sys) computes the Kalman decomposition of a
%   state-space realization and returns the dimensions of the controllable
%   and observable subspace of A.
%   
%   [A, B, C, D] = DECOMPOSE(sys) computes the Kalman decomposition of a
%   state-space realization and returns the controllable and observable
%   subspace of the system.

%   References:
%   R. E. Kalman, "On the Computation of the Reachable/Observable 
%   Canonical Form," SIAM J. Control and Optimization, Vol. 20, No. 2, 
%   pp. 258-260, 1982
% 
%   http://ece.iit.edu/~gaw/ece531/ECE531_18S_kalman.pdf
%   https://ece.gmu.edu/~gbeale/ece_521/xmpl-521-kalman-min-real-01.pdf

p = inputParser;
addRequired(p, 'sys', @(S) validatesystem(S, {'full'}));
parse(p, sys);

[A, B, C, ~] = getabcd(sys);

% Find the controllability and observability matrices. 
Co = ctrbs(A, B);
Ob = obsvs(A, C);

% Compute an orthonormal transformation matrix.
P = orth([Co, null(Ob), eye(size(A))], 'real');

% Compute the Kalman decomposition of the system.
T = symss2symss(sys, P.');

nout = nargout;
if nout == 1
    varargout{1} = T;
else
    nc = rank(Co);
    no = rank(Ob);
    
    if nout == 2
        varargout{1} = T;
        varargout{2} = [nc, no];
    elseif nargout > 3
        n = min([nc, no]);
        varargout{1} = T.A(1:n, 1:n);
        varargout{2} = T.B(1:n, :);
        varargout{3} = T.C(:, 1:n);
        if nout == 4
            varargout{4} = T.D;
        end
    end
end

end

