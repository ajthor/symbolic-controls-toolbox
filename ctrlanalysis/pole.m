function p = pole(sys)
%POLE Computes the poles of a system.
%   Detailed explanation goes here
if isa(sys, 'symss')
    sys = symss2symtf(sys);
end

p = double(root(sys.Denominator));

end

