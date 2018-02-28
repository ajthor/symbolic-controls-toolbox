classdef symssTest < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testSystemCreation(testCase)
            % define syntax
            syms x1 x2 u1

            sys = symss;
            sys.states = [x1 x2];
            sys.inputs = u1;

            sys.f(1) = x1;
            sys.f(2) = x2 + u1;
            
            testCase.verifyNumElements(sys.states, 2);
        end
        
        function testNestedStateVariables(testCase)
            % define syntax
            syms x1 x2 x3 u1

            sys = symss;
            sys.states = [x1, [x2, x3]];
            sys.inputs = u1;

            sys.f(1) = x1;
            sys.f(2) = x2 + u1;
            
            testCase.verifyNumElements(sys.states, 3);
        end
    end
end

