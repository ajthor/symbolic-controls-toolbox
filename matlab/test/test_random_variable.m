classdef test_random_variable < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here

    methods(Test)
        function testRandomVarSampling(testCase)
            X = randomvar('X');

            testCase.verifyEqual(X.sym(), sym('X'));

            gen = randomdevice();
            testCase.verifyTrue(isnumeric(X.sample(gen)));
        end
    end
end
