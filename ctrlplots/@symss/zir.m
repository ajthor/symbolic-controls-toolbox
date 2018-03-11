function Yi = zir(sys, x0)
%ZIR Get the zero input response of a system.
%   The zero input response is defined as:
% 
%                    -1
%   Yi(s) = C(sI - A)  x(0)
% 
%   And equivalently in the time domain:
%   
%             At
%   yi(t) = Ce  x(0)
% 

[~, ~, C, ~] = getmatrices(sys);
Phi = stm(sys);

Yi = C*Phi*x0;

end

