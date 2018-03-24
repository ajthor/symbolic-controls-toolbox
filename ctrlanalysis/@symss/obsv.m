function Ob = obsv(sys)
%OBSV Computes the observability matrix of a state space model.
%   
%   Ob = OBSV(sys) returns the observability matrix
%   
%       [C; C*A; C*A^2; ...]
% 
%   See also obsvs

[A, ~, C, ~] = sys.getabcd();
Ob = obsvs(A, C);

end

