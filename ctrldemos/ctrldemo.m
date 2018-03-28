function D = ctrldemo(name, varargin)
%CTRLDEMO Loads a demo system from memory.
% 
%   Available demo systems:
%       - pendulum (No friction)
%       - pendulum2 (No constants)
%       - pendulum3 (With constants)
%       - vanderpol (Van der Pol equation)

p = inputParser;
validateName = @(arg) validateattributes(arg, {'char', 'string'}, {'nonempty'});
addRequired(p, 'name', validateName);
parse(p, name, varargin{:});

S = load(name);
D = S.sys;

end

