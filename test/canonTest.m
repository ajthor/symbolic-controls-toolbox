classdef canonTest < matlab.unittest.TestCase
    %CANONTEST Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        system1
        system2
    end
    
    methods(TestMethodSetup)
        function loadSystems(testCase)
            % load systems
            A = [0, 1; -2, -3];
            B = [0; 1];
            C = [3, 1];
            D = 0;
            testCase.system1 = symss(A, B, C, D);
            testCase.system2 = ctrldemo('massspring');
        end
    end
    
    methods (Test)
        function testControllableCanonicalForm(testCase)
            % should convert state space to controllable canonical form.
            T1 = canon(testCase.system1, 'c');
            T2 = canon(testCase.system2, 'c');
            
            syms(symvar(T2.f));
            syms(symvar(T2.g));
            
            testCase.verifyEqual(T1.A, sym([0, 1; -2, -3]));
            testCase.verifyEqual(T1.B, sym([0; 1]));
            testCase.verifyEqual(T1.C, sym([3, 1]));
            
            testCase.verifyEqual(T2.A, sym([0, 1; -K/M, -C/M]));
            testCase.verifyEqual(T2.B, sym([0; 1]));
            testCase.verifyEqual(T2.C, sym([B/M, 0]));
            
            testCase.verifyEqual(eig(testCase.system1.A), eig(T1.A));
            testCase.verifyEqual(eig(testCase.system2.A), eig(T2.A));
        end
        
        function testObservableCanonicalForm(testCase)
            % should convert state space to observable canonical form.
            T1 = canon(testCase.system1, 'o');
            T2 = canon(testCase.system2, 'o');
            
            syms(symvar(T2.f));
            syms(symvar(T2.g));
            
            testCase.verifyEqual(T1.A, sym([0, -2; 1, -3]));
            testCase.verifyEqual(T1.B, sym([3; 1]));
            testCase.verifyEqual(T1.C, sym([0, 1]));
            
            testCase.verifyEqual(T2.A, sym([0, -K/M; 1, -C/M]));
            testCase.verifyEqual(T2.B, sym([B/M; 0]));
            testCase.verifyEqual(T2.C, sym([0, 1]));
            
            testCase.verifyEqual(eig(testCase.system1.A), eig(T1.A));
            testCase.verifyEqual(eig(testCase.system2.A), eig(T2.A));
        end
        
        function testJordanCanonicalForm(testCase)
            % should convert state space to Jordan canonical form.
            T1 = canon(testCase.system1, 'j');
            
            testCase.verifyEqual(T1.A, sym([-2, 0; 0, -1]));
            testCase.verifyEqual(T1.B, sym([2; -1]));
            testCase.verifyEqual(T1.C, sym([-1/2, -2]));
            
            testCase.verifyEqual(eig(testCase.system1.A), eig(T1.A));
        end
        
        function testKalmanCanonicalForm(testCase)
            % should convert state space to Kalman canonical form.
            T1 = canon(testCase.system1, 'k');
            
            testCase.verifyEqual(T1.A, sym([-3, -2; 1, 0]));
            testCase.verifyEqual(T1.B, sym([1; 0]));
            testCase.verifyEqual(T1.C, sym([1, 3]));
            
            testCase.verifyEqual(eig(testCase.system1.A), eig(T1.A));
        end
    end
end

