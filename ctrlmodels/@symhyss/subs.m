function T = subs(sys, varargin)
%SUBS Replace symbolic variables in hybrid state space model.

T = copy(sys);

for k = 1:T.nmodes
    T.f_{k} = subs(T.f_{k}, varargin{:});
end

T.g = subs(T.g, varargin{:});

end
