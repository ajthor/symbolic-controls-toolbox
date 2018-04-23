function [X, Xf] = dspace(sys, blocks, varargin)
%DSPACE Discretize a state-space into blocks.
%
%   X = DSPACE(sys, blocks) computes a discretized state space for use with
%   an MDP.
%
%   The function partitions a continuous state space into discrete chunks,
%   allowing the MDP to utilize a discretized model for planning.
%
%   The function returns a symbolic matrix of inequalities, which can be
%   used to determine the current partition the state is currently in.
%
%   For example, discretizing a 2-D state space using the following
%   command:
%
%   X = DSPACE(sys, {[0, 3, 8, 10], [0, 2, 5]})
%
%   would create the following space discretization:
%
%     x2
%     ^
%     |
%   5 +- - - - - - - + - - - - - - - - - - - -+- - - - -+
%     |              |                        |         |
%   4 +              |                        |         |
%     |    {1,2}     |         {2,2}          |  {3,2}  |
%   3 +              |                        |         |
%     |              |                        |         |
%   2 +- - - - - - - + - - - - - - - - - - - -+- - - - -+
%     |              |                        |         |
%   1 +    {1,1}     |         {2,1}          |  {3,1}  |
%     |              |                        |         |
%   0 +----+----+----+----+----+----+----+----+----+----+-> x1
%     0    1    2    3    4    5    6    7    8    9    10
%
%   The symbolic matrix is indexed according to the states. For example,
%
%   X(x1, x2, x3, ...)
%
%   For the above example, this means that for {x1 = 9, x2 = 3}, the
%   partition which would return a 1 when the equalities are evaluated
%   would be {3, 2}.
%
%   The inequalities default to include the bounds to the right, meaning
%   for {x1 = 8, x2 = 2} in the above example, the partition that would
%   return a 1 would be {2, 1}. In order to flip the inequalities, set the
%   'LeftInequalities' parameter to true. If set, the above example would
%   evaluate to partition {3, 2}.
%
%   Example:
%       syms x1 x2
%       m = mdp
%       m.states = [x1, x2]
%       [X, Xf] = DSPACE(m, {[0, 3, 8, 10], [0, 2, 5]})
%       [x1, x2] = ind2sub(size(X), Xf(5, 2))
%
%   Outputs:
%       x1 = 2
%       x2 = 1
%
%   See also mdp

p = inputParser;
addRequired(p, 'sys');
addRequired(p, 'blocks');
addParameter(p, 'LeftInequalities', false)
parse(p, sys, blocks, varargin{:});

left = p.Results.LeftInequalities;

blocks = reshape(p.Results.blocks, 1, []);
for b = blocks
    validateattributes(b{:}, {'numeric'}, {'increasing'});
end
sz = arrayfun(@(x) length(x{:}), blocks);
n = numel(sz);

L = cell(1, n);
[L{:}] = ndgrid(blocks{:});

X = sym(ones(sz - 1));
idx = cell(size(sz));

for k = 1:numel(L)
    d = L{k};

    for m = 1:numel(d)
        [idx{:}] = ind2sub(sz, m);
        if any([idx{:}] >= sz)
            continue;
        end

        ni = num2cell([idx{:}] + 1);

        if left
            % Bounds are to the left.
            X(idx{:}) = ...
                        d(idx{:}) <= sys.states(k) ...
                        & sys.states(k) < d(ni{:}) ...
                        & X(idx{:});
        else
            % Default behavior. Bounds are to the right.
            X(idx{:}) = ...
                        d(idx{:}) < sys.states(k) ...
                        & sys.states(k) <= d(ni{:}) ...
                        & X(idx{:});
        end
    end
end

% Create helper function.
Xf = symfun(X, sys.states);
Xf = @(varargin) find(isAlways(Xf(varargin{:})));

end
