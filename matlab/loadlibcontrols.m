function loadlibcontrols()

addpath(fileparts(mfilename('fullpath')));

if not(libisloaded('libctrl'))
    loadlibrary('libctrl');
end

libfunctions('libctrl')

end
