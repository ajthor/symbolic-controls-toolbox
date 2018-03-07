function sys = subs(sys, varargin)
%SUBS Replace symbolic variables in state space model.
%   
%   sys = SUBS(sys, ...) replaces symbolic variables in a state space
%   model. 
%   
%   It is possible to replace state variables and input variables
%   using this method as well as symbolic variables and symbolic functions
%   present in the state equations.
% 
%   sys = SUBS(sys, new) replaces state variables or input variables in the
%   state space model.
%   
%   sys = SUBS(sys, old, new) replaces symbolic variables or symbolic
%   functions in the state equations.
% 
%   See also sym/subs

switch nargin
    case 1
        sys = simplify(sys);
        
    case 2
        old = reshape([sys.states; sys.inputs], [], 1);
        new = reshape(varargin{:}, [], 1);

        sys.states = subs(sys.states, old, new);
        sys.inputs = subs(sys.inputs, old, new);
        sys.f = subs(sys.f, old, new);
        sys.g = subs(sys.g, old, new);
    
    otherwise
        sys.f = subs(sys.f, varargin{:});
        sys.g = subs(sys.g, varargin{:});
end

end
