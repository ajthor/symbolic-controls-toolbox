classdef (SupportExtensionMethods = true) mdp < handle

    properties (Access = private, Hidden = true)
        cobj_;
    end

    properties (Dependent)
        S
        A
        % P
        % R
        gamma
    end

    methods
        function obj = mdp()
            obj.cobj_ = calllib('matctrl', 'mdp_new');
        end

        function delete(obj)
            calllib('matctrl', 'mdp_free', obj.cobj_);
        end
    end

    methods
        function S = get.S(obj)
            S = calllib('matctrl', 'mdp_get_num_states', obj.cobj_);
        end

        function set.S(obj, n)
            calllib('matctrl', 'mdp_set_num_states', obj.cobj_, n);
        end

        function A = get.A(obj)
            A = calllib('matctrl', 'mdp_get_num_inputs', obj.cobj_);
        end

        function set.A(obj, n)
            calllib('matctrl', 'mdp_set_num_inputs', obj.cobj_, n);
        end

        function gamma = get.gamma(obj)
            gamma = calllib('matctrl', 'mdp_get_gamma', obj.cobj_);
        end

        function set.gamma(obj, gamma)
            calllib('matctrl', 'mdp_set_gamma', obj.cobj_, gamma);
        end
    end
end
