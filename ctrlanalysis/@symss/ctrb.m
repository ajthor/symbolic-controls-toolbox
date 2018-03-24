function Co = ctrb(sys)
%CTRB Computes the controllability matrix of a state space model.
%   
%   Co = CTRB(sys) returns the controllability matrix 
%   
%       Co = [B, A*B, A^2*B, ...]
% 
%   See also ctrbs

[A, B, ~, ~] = sys.getabcd();
Co = ctrbs(A, B);

end

