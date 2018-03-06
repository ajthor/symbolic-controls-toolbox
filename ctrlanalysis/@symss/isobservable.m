function tf = isobservable(sys)
%ISOBSERVABLE Uses the eigenvector test to determine if a system is
%observable. It returns a logical 1 (true) if the system is observable and
%a logical 0 (false) if it is not.

if isa(sys, 'symtf')
    sys = symtf2symss(sys);
end
[A, ~, C, ~] = sys.getMatrices();

n = length(A);
L = eig(A);
Ob = zeros(1:numel(L));

for k = 1:numel(L)
    Ob(k) = rank([(L(k)*eye(n) - A); C]);
end

tf = ~any(Ob < n);

end

