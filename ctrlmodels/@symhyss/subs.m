function sys = subs(sys, varargin)
%SUBS Replace symbolic variables in hybrid state space model.

for k = 1:numel(sys.f)
    sys.f{k} = subs(sys.f(k), varargin{:});
end

sys.g = subs(sys.g, varargin{:});

end

