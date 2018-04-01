function T = kalmanform(sys)
%KALMANFORM Kalman decomposition.
%   
%   T = KALMANFORM(sys) converts a state space model to its Kalman
%   decomposition.

[A, B, C, ~] = getabcd(sys);

% Find the controllability and observability matrices. 
Co = ctrbs(A, B);
Ob = obsvs(A, C);

% Compute an orthonormal transformation matrix.
P = orth([Co, null(Ob), eye(size(A))], 'real');

% Compute the Kalman decomposition of the system.
T = symss2symss(sys, P.');

end

