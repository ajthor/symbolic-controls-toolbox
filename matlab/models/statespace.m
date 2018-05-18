classdef (SupportExtensionMethods = true) statespace < handle

    properties (Access = private, Hidden = true)
        cobjHandle;
    end

    methods
        function obj = statespace(varargin)
            obj.cobjHandle = statespace_new(varargin);
        end

        function delete(obj)
            statespace_free(obj.cobjHandle);
        end
    end

end
