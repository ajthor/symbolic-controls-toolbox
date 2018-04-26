function varargout = propp(m, uidx, pattern)
%PROPP Propagate probability pattern through matrix.
%
%   P = PROPP(m, uidx, pattern)
%
%   Propagate probability pattern through matrix.
%   m - mdp object
%   uidx - input index
%   pattern - probability pattern
%
%   The probability pattern has the form: {[idx], [probability]}
%
%   Specify ignored values of the state with NaN. Specify the pattern as a
%   matrix centered around the current state.
%
%   For example, if the state space is the canonical grid world example,
%   with two states, X and Y, and one input, such as "move forward", we
%   propagate the probabilities through the matrix by specifying the
%   pattern as:
%
%   P = pprop(m, 1, {[NaN, NaN], [0, 0.8, 0; 0.1, NaN, 0.1; 0, 0, 0]});
%
%   In effect, this will iterate over all values of X and Y and place the
%   pattern on top of the probability matrix. For this example, X and Y
%   form a NxP matrix, where N is the number of discrete values for X, and
%   P is the number of discrete values of Y. The grid coordinates with an
%   overlaid pattern may be displayed like below.
%
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%       |  0  | 0.8 |  0  |     |       |     |  0  | 0.8 |  0  |
%       +-----+--^--+-----+-----+       +-----+-----+--^--+-----+
%       | 0.1 |  X  | 0.1 |     |       |     | 0.1 |  X  | 0.1 |
%     Y +-----+-----+-----+-----+  -->  +-----+-----+-----+-----+
%       |  0  |  0  |  0  |     |       |     |  0  |  0  |  0  |
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%       |     |     |     |     |       |     |     |     |     |
%       +-----+-----+-----+-----+       +-----+-----+-----+-----+
%                   X
%
%   However, the probability matrix defines a from/to relationship, so the
%   probability matrix is an NxNxP matrix.
%
%   This means that the X/Y coordinate matrix above has 16 possible states.
%
%       +-----+-----+-----+-----+
%       |  1  |  5  |  9  | 13  |
%       +-----+-----+-----+-----+
%       |  2  |  6  | 10  | 14  |
%       +-----+-----+-----+-----+
%       |  3  |  7  | 11  | 15  |
%       +-----+-----+-----+-----+
%       |  4  |  8  | 12  | 16  |
%       +-----+-----+-----+-----+
%
%   This implies that the probability matrix is a 16x16x1 matrix for the
%   grid world example with one input, where each element in the matrix
%   represents the conditional probability
%
%     P{x'|x, u}
%
%               To
%          From \      1           2           3
%                +-----------+-----------+-----------+
%              1 | P{1|1, 1} | P{2|1, 1} | P{3|1, 1} |
%                +-----------+-----------+-----------+
%              2 | P{1|2, 1} | P{2|2, 1} | P{3|2, 1} | ...
%                +-----------+-----------+-----------+
%              3 | P{1|3, 1} | P{2|3, 1} | P{3|3, 1} |
%                +-----------+-----------+-----------+
%                                 ...

p = inputParser;
addRequired(p, 'm');
addRequired(p, 'uidx', ...
    @(arg) validateattributes(arg, {'numeric'}, ...
                              {'scalar', 'positive', '<=', length(m.U)}));
addRequired(p, 'pattern', ...
    @(arg) validateattributes(arg, {'cell'}, {'size', [NaN, 2]}));
parse(p, m, uidx, pattern);

validateattributes(pattern{1}, {'numeric'}, {'size', [1, ndims(m.X)]});
validateattributes(pattern{2}, {'numeric'}, ...
                               {'nonnegative', 'ndims', ndims(m.X)});

psum = sum(pattern{2}(:), 'omitnan');
if psum > 1
    error('Probabilities in pattern must not exceed 1.');
else
    nanval = 1 - psum;
end

if numel(find(isnan(pattern{2}))) ~= 1
    error('Pattern must have exactly one ''NaN'' value.');
end

idx = num2cell(pattern{1});

% Replace NaN values in indices.
for k = 1:numel(idx)
    if isnan(idx{k})
        idx{k} = 1:size(m.X, k);
    end
end

% Get the subscripts for the pattern indices.
Z = zeros(size(m.X));
Z(idx{:}) = 1;
pidx = find(Z);
Z(idx{:}) = 0;

% Convert pattern to an array.
psz = num2cell(size(pattern{2}));
for k = 1:numel(psz)
    psz{k} = 1:psz{k};
end

Z(psz{:}) = pattern{2};
% Z = reshape(Z, 1, []);
zidx = find(isnan(Z));
% Z(zidx) = nanval;

nidx = numel([idx{:}]);

P = m.P;

for k = 1:numel(pidx)
    Zt = squeezepattern(m.X, Z, pidx(k));
    Zt = reshape(Zt, 1, []);
    
    Zt(isnan(Zt)) = 1 - sum(Zt, 'omitnan');
    
%     P(pidx(k), pidx(k):pidx(k) + length(Zt) - 1, uidx) = Zt;
    P(pidx(k), 1:length(Zt), uidx) = Zt;
    
%     if pidx(k) < zidx
% %         prerem = sum(pre(1:pidx(k) - 1));
% %         postrem = sum(post(pidx(k) + 1:
% 
%         P(pidx(k), 1:pidx(k) - 1, uidx) = pre(end - pidx(k) + 1:end);
%         P(pidx(k), pidx(k), uidx) = post(1);
%         P(pidx(k), pidx(k) + 1, uidx) = post(2:end);
% 
% %         P(pidx(k), 1:pidx(k) - 1, uidx) = Z(zidx - pidx(k) + 1:zidx - 1);
% %
% %         P(pidx(k), pidx(k):pidx(k) + nidx - zidx, uidx) = Z(zidx:end);
% %
% %         P(pidx(k), pidx(k), uidx) = Z(pidx(k)) + rem;
%     elseif pidx(k) > zidx
% %         rem = sum(Z(zidx + 1:end));
% %
% %         P(pidx(k), pidx(k) - nidx + zidx:pidx(k) - 1, uidx) = Z(1:zidx - 1);
% %
% %         P(pidx(k), pidx(k):end, uidx) = Z(zidx:pidx(k) - zidx) + rem;
%     else
%         P(pidx(k), :, uidx) = Z(:);
%     end
end

if nargout ~= 0
    varargout{1} = P;
else
    m.P = P;
end

end
