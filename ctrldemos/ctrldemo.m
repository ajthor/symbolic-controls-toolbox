function D = ctrldemo(name, varargin)
%CTRLDEMO Loads a demo system from memory.
% 
%   Detailed explanation goes here

p = inputParser;
validateName = @(arg) validateattributes(arg, {'char', 'string'}, {'nonempty'});
addRequired(p, 'name', validateName);
parse(p, name, varargin{:});

S = load(name);
D = S.sys;

end

