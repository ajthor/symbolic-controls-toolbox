function [x, u, f, g] = varsub(obj, varargin)
%VARSUB Replaces variables with dummy variables for symbolic operations.

nx = cell(size(obj.states_));
nx(:) = {'SUBX'};

nu = cell(size(obj.inputs_));
nu(:) = {'SUBU'};

x = sym(genvarname(nx));
u = sym(genvarname(nu));

f = subs(obj.f_, [obj.states_; obj.inputs_], [x; u]);
g = subs(obj.g_, [obj.states_; obj.inputs_], [x; u]);

end

