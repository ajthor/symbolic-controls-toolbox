function varargout = lyap(sys, varargin)
%LYAP Solves the lyapunov equation for a system.
%   
%   V = LYAP(sys) 
%   solves the Lyapunov matrix equation A.'*P + P*A + Q == 0 for the
%   symbolic state space model and returns the equation V = x.'*P*x. The
%   function solves the Lyapunov matrix equation using the Hamiltonian
%   matrix H = [A, 0; -Q, -A.'].
%   
%   V = LYAP(sys, Q) solves the Lyapunov matrix equation for the symbolic
%   state space model using the matrix Q. If Q is unspecified, the function
%   uses the identity matrix I.
% 
%   [V, P, dV] = LYAP(sys, Q) solves the Lyapunov matrix equation and
%   returns the Lyapunov function, the solution P, and the Lyapunov
%   function derivative.
% 
%   Tips:
%   - If a solution cannot be found, the function emits a warning and
%   returns a zero result.
% 
%   - Use a linearized system for nonlinear state space models if a result
%   cannot be obtained.
% 
%   - Rank-deficient state matrices will not produce a unique result, and
%   the P matrix will not be symmetric. Check the rank of A before running
%   the function.
% 
%   See also symss/care, lyap, dlyap

p = inputParser;
[A, ~, ~, ~] = getabcd(sys);
validateMatrix = @(M) isequal(M, M.') && isequal(size(M), size(A));
addRequired(p, 'sys')
addOptional(p, 'Q', eye(size(A), 'like', A), validateMatrix);
parse(p, sys, varargin{:});

Q = p.Results.Q;

if ~ishurwitz(A)
    error('State matrix is not Hurwitz.');
end


% METHOD 1
% Construct Hamiltonian
% H = [A, eye(size(A)); -Q, -A.'];
% [U, ~] = qr(H, 'real');
% U = mat2cell(U, size(A), size(A));
% P = U{2, 1}/U{1, 1};

% METHOD 2
% [V, D] = eig(H);
% D = reshape(diag(D), 1, []);
% 
% % rL = D(~all(isAlways(real(D) < 0) == 0, 1));
% % rV = cellfun(@(L) {null(H - L*eye(size(H)))}, sym2cell(rL));
% 
% rV = V(:, ~all(isAlways(real(D) < 0) == 0, 1));
% XY = mat2cell(rV, [length(A), length(A)]);
% 
% P = XY{2}/XY{1};

% METHOD 3
% P = sym('P', size(A));
% S = solve(A.'*P + P*A == -Q, P);
% P = subs(P, S);

% METHOD 4
% [V, D, p] = eig(H);
% VV = zeros(size(H));
% for k = 1:size(V, 2)
%     idx = p(k);
%     L = any(D == D(idx, idx), 1);
%     VV(:, L) = repmat(V(:, k), 1, nnz(L));
% end
% 
% XY = VV(:, ~any(isAlways(real(diag(D)) < 0) == 0, 2));
% XY = mat2cell(XY, [length(A), length(A)]);
% 
% P = XY{2}/XY{1};

% METHOD 5
H = [A, zeros(size(A)); -Q, -A.'];
[V, D, P] = eig(H);
% Form a basis when the matrix has non-linearly independent eigenvectors.
if ~isequal(size(V), size(H))
    Vf = sym(zeros(size(H)));
    for k = 1:size(V, 2)
        L = any(D == D(P(k), P(k)), 1);
        Vf(:, L) = repmat(V(:, k), 1, nnz(L));
    end
    V = Vf;
end
[~, idx] = sort(diag(real(D)));
V = V(:, idx);
[U, ~] = qr(V, 'real');
U = mat2cell(U, size(A), size(A));
P = U{2, 1}/U{1, 1};

varargout{1} = sys.states.'*P*sys.states;
varargout{2} = P;
varargout{3} = -sys.states.'*Q*sys.states;
if varargout{1} == 0
    warning('Could not find a solution to the Lyapunov equation.');
end

end

