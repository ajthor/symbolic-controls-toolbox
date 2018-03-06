function tf = issquare(A)
%ISSQUARE Summary of this function goes here
%   Detailed explanation goes here
[n, m] = size(A);
tf = isequal(n, m);

end

