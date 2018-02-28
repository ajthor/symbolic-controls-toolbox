function [x, u, f, g] = varSub(obj, varargin)
%VARSUB Replaces variables with dummy variables for symbolic operations.

nx = cell(size(obj.states));
nx(:) = {'SUBX'};

nu = cell(size(obj.inputs));
nu(:) = {'SUBU'};

x = sym(genvarname(nx));
u = sym(genvarname(nu));

f = subs(obj.f, [obj.states obj.inputs], [x u]);
g = subs(obj.g, [obj.states obj.inputs], [x u]);

end

