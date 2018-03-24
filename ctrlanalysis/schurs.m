function [U, S] = schurs(H, varargin)
%SCHURS Symbolic Schur decomposition.

p = inputParser;
validateMatrix = @(M) validateattributes(M, {'sym', 'numeric'}, {'nonempty'});
validateSteps = @(s) validateattributes(s, {'numeric'}, {'integer'});
addRequired(p, 'H', validateMatrix);
addParameter(p, 'steps', 10, validateSteps);
parse(p, H, varargin{:});

steps = p.Results.steps;

% HB = feval(symengine, 'linalg::hessenberg', H);
if ~isa(H, 'sym')
    H = sym(H);
end

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

[~, idx] = sort(diag(D), 'descend');
V = V(:, idx);

% HB = H;
[U, ~] = qr(V, 'real');

% for k = 1:steps
%     [Q, R] = qr(HB, 0);
%     HB = Q*R;
% end
% U = Q;
S = U.'*H*U;

end

