function savedemo(name, sys)
%SAVEDEMO Save system to file.
%   Detailed explanation goes here

p = inputParser;
validateName = @(arg) validateattributes(arg, {'char', 'string'}, {'nonempty'});
addRequired(p, 'name', validateName);
addRequired(p, 'sys')
parse(p, name, sys);

[folder, ~, ~] = fileparts(mfilename('fullpath'));
name = fullfile(folder, name);
save(name, 'sys')

end

