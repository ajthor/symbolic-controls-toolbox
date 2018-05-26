function loadmatctrl()

if ~libisloaded('matctrl')
    addpath(fullfile(userpath, 'matctrl'));
    loadlibrary('matctrl', 'include/matlab_wrapper.h');
end

libfunctions('matctrl')

end
