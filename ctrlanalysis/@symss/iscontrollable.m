function tf = iscontrollable(sys)
%ISCONTROLLABLE Uses the eigenvector test to determine if a system is
%controllable. It returns a logical 1 (true) if the system is controllable
%and a logical 0 (false) if it is not.

sys = symss(sys);
[A, B, ~, ~] = sys.getmatrices();

n = length(A);
L = eig(A);
Co = zeros(1:numel(L));

for k = 1:numel(L)
    Co(k) = rank([(L(k)*eye(n) - A), B]);
end

tf = ~any(Co < n);

end

