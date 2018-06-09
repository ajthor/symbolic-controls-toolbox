function X = mat2se(A)

X = cell(size(A));

if ~iscell(A)
    if isnumeric(A)
        X = num2cell(A);
        X = cellfun(@(x) {num2str(x)}, X);
    elseif isa(A, 'sym')
        X = sym2cell(A);
        X = cellfun(@(x) {char(x)}, X);
    end
end

% X(:) = {'0'};
%
% for k = 1:numel(A)
%     if isnumeric(A{k})
%         X{k} = num2str(A{k});
%     elseif isa(A{k}, 'sym')
%         X{k} = char(A{k});
%     end
% end

end
