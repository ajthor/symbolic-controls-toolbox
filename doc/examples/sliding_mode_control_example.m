A = [1 1 1; 0 1 3; 1 0 1];
B = [0 1; 1 -1; -1 0];

syms x1 x2 x3 u1 u2

sys = symss;
sys.states = [x1, x2, x3];
sys.inputs = [u1, u2];

sys.f = A*sys.states + B*sys.inputs;
sys.g(1) = 0;

% s = slide(sys)

%%
S = slide(sys, diag([1, 2, 3]));

uSM = slidectrl(sys, S);

%%
nlsim(sys, uSM, [0 10], {[1, 1, 1]});

%%

odefun = matlabFunction(sys.B*uSM, 'Vars', {sym('t'), sys.states});
[tu, yu] = ode45(odefun, [0 10], [1, 0, 1]);

plot(tu, yu)
