classdef (SupportExtensionMethods = true) mdp < handle

    properties (Access = private, Hidden = true)
        cobjHandle;
    end

    properties (Dependent)
        S
        A
        P
        R
        gamma
    end

    methods
        function obj = statespace()
            obj.cobjHandle = calllib('matctrl', 'mdp_new');
        end

        function delete(obj)
            calllib('matctrl', 'mdp_free', obj.cobjHandle);
        end
    end

    methods
        function S = get.S(obj)
            S = calllib('matctrl', 'mdp_get_num_states', obj.cobjHandle);
        end

        function set.S(obj, n)
            calllib('matctrl', 'mdp_set_num_states', obj.cobjHandle, n);
        end

        function A = get.A(obj)
            A = calllib('matctrl', 'mdp_get_num_inputs', obj.cobjHandle);
        end

        function set.A(obj, n)
            calllib('matctrl', 'mdp_set_num_inputs', obj.cobjHandle, n);
        end

        function gamma = get.gamma(obj)
            gamma = calllib('matctrl', 'mdp_get_gamma', obj.cobjHandle);
        end

        function set.gamma(obj, gamma)
            calllib('matctrl', 'mdp_set_gamma', obj.cobjHandle, gamma);
        end
    end
end
