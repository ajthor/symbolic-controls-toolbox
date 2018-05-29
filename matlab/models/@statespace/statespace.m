classdef (SupportExtensionMethods = true) statespace < handle

    properties (Access = protected, Hidden = true)
        cobj_;
    end

    properties (Dependent)
        states
    end

    methods
        function obj = statespace(varargin)
            obj.cobj_ = calllib('matctrl', 'statespace_new');
        end

        function delete(obj)
            calllib('matctrl', 'statespace_free', obj.cobj_);
        end
    end

    methods
        function set.states(obj, s)
            validateattributes(s, {'char', 'sym'}, {'scalar'});
            calllib('matctrl', 'statespace_set_state', obj.cobj_, 0, s);
        end

        function states = get.states(obj)
            states = calllib('matctrl', 'statespace_get_states', obj.cobj_);
        end
    end

end
