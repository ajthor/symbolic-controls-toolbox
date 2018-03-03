function z = zero(sys)
%ZERO Computes the zeros of a system.
%   Detailed explanation goes here
if isa(sys, 'symss')
    sys = symss2symtf(sys);
end

z = double(root(sys.Numerator));

end

