%% Thermostat Demo System
% 
% a - temperature cooling coeficient, a < 1
syms a

syms x1 u
sys = symhyss;
sys.states = x1;

sys.f(1, 1) = -a*x1;
sys.cond(1, 2) = x1 >= 20;

sys.f(2, 1) = -a*(x1 - 30);
sys.cond(2, 1) = x1 <= 22;

savedemo('thermostat', sys, {a});
