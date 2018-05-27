classdef (SupportExtensionMethods = true) statespace < handle

    properties (Access = private, Hidden = true)
        cobjHandle;
    end

    methods
        function obj = statespace()
            obj.cobjHandle = calllib('matctrl', 'statespace_new');
        end

        function delete(obj)
            calllib('matctrl', 'statespace_free', obj.cobjHandle);
        end
    end

end
