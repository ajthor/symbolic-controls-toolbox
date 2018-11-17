classdef test_ode < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here

    methods(Test)
        function testOdeEulerMethod(testCase)
            % sym
            syms x

            sys = statespace();
            sys.states = x;
            sys.f = 2*x + 1;

            [t, y] = ode_euler(sys, [0, 0.1], 1);

            testCase.verifyEqual(t(1), 0, 'AbsTol', 1E-3);
            testCase.verifyEqual(y(1), 1, 'AbsTol', 1E-3);
            testCase.verifyEqual(t(101), 0.1, 'AbsTol', 1E-3);
            testCase.verifyEqual(y(101), 1.3317, 'AbsTol', 1E-3);
        end
    end
end
