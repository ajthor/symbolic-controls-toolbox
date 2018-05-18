function loadcontrolslib()

addpath(fileparts(mfilename('fullpath')));

if not(libisloaded('controlslib'))
    loadlibrary('controlslib');
end

libfunctions('controlslib')

end
