function ts = gettsdata(f, rg)
%GETTSDATA Get time-series data for a function.
%   Detailed explanation goes here
syms t
Ffun = symfun(formula(f), t);
ts = Ffun(rg);

if length(ts) > 1
    for k = 1:numel(ts)
        ts(k) = {double(ts{k})};
    end
end

end

