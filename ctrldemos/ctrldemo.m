function D = ctrldemo(name, varargin)
%CTRLDEMO Loads a demo system from memory.
% 
%   Available demo systems:
%       - massspring    (
%       - pendulum      (No friction)
%       - pendulum2     (No constants)
%       - pendulum3     (With constants)
%       - quadrotor     (Quadrotor, euler angles)
%       - vanderpol     (Van der Pol equation, forward time)
%       - vanderpol2    (Van der Pol equation, reverse time)

p = inputParser;
validateName = @(arg) ...
    validateattributes(arg, {'char', 'string'}, {'nonempty'});
addRequired(p, 'name', validateName);
parse(p, name, varargin{:});

% Load the system.
S = load(name);
D = S.sys;

% Define constants in caller workspace.
for k = S.C{:}
    assignin('caller', char(k{:}), k{:});
end

end

