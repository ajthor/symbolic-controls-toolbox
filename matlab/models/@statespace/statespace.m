classdef (SupportExtensionMethods = true) statespace < handle

    properties (Access = private, Hidden = true)
        cobj_;
    end

    methods
        function obj = statespace()
            obj.cobj_ = calllib('matctrl', 'statespace_new');
        end

        function delete(obj)
            calllib('matctrl', 'statespace_free', obj.cobj_);
        end
    end

end
