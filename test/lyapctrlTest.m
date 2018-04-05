classdef lyapctrlTest < matlab.unittest.TestCase
    %LYAPCTRLTEST Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testCtrllyapNonlinear(testCase)
            % should compute a control input.
            syms x u a b
            sys = symss;
            sys.states = x;
            sys.inputs = u;

            sys.f(1) = a*x - b*x^3 + u;
            sys.g(1) = x;

            V = x^2/2;

            U = lyapctrl(sys, V);
            
            ref = -(x*(- b*x^3 + a*x) + ...
                  (x^2*(- b*x^3 + a*x)^2 + x^4)^(1/2))/x;
            
            testCase.verifyEqual(U, ref);
        end
    end
end

