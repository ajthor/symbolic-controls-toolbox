function [K, P, L] = lqr(sys, Q, R)
%LQR Summary of this function goes here
%   Detailed explanation goes here

A = sys.A;
B = sys.B;

P = care(sys, Q, R);

K = inv(R)*B.'*P;
L = eig(A - B*K);

end

