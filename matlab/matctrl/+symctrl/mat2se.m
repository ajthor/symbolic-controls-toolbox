function X = mat2se(A)

X = cell(size(A));

switch (class(A))
    case 'cell'
        X = cellfun(@(x) {char(x)}, A);
    case 'string'
        X = cellstr(A);
    case 'char'
        X = {A};
    case 'sym'
        X = sym2cell(A);
        X = cellfun(@(x) {char(x)}, X);
    otherwise
        if isnumeric(A)
            X = num2cell(A);
            X = cellfun(@(x) {num2str(x)}, X);
        else
            error('SYMCTRL::InvalidInput', 'Cannot convert input to C type.');
        end
end

% if ~iscell(A)
%     if isnumeric(A)
%         X = num2cell(A);
%         X = cellfun(@(x) {num2str(x)}, X);
%     elseif isa(A, 'sym')
%         X = sym2cell(A);
%         X = cellfun(@(x) {char(x)}, X);
%     elseif ischar(A)
%         X = {A};
%     end
% else
%     % Input is a cell. Convert the inputs to strings.
%     X = cellfun(@(x) {char(x)}, A);
% end

end
