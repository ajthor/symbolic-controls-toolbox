function Ob = obsvs(A, C)
%OBSVS Symbolic observability matrix
% 
%   Ob = OBSVS(A, C) returns the observability matrix 
%       Ob = [C; C*A; C*A^2; ...]
p = inputParser;
validateA = @(A) validateattributes(A, {'sym'}, {'square', 'nonempty'});
validateC = @(C) validateattributes(C, {'sym'}, {'nonempty'});
addRequired(p, 'A', validateA);
addRequired(p, 'C', validateC);
parse(p, A, C);

nx = size(A, 1);
[cr, ~] = size(C);

Ob = sym('Ob', [cr*nx nx]);

Ob(1:cr, :) = C;

for k = 2:nx
    prev = cr*(k - 2)+1:cr*(k - 1);
    next = cr*(k - 1)+1:cr*k;
    
    Ob(next,:) = Ob(prev,:)*A;
end

end
