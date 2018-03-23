clear, clc
syms k x(t)

sys = symss;
sys.states = [x, diff(x)];

sys.f(1) = diff(x);
sys.f(2) = -k*sin(x);
sys.g(1) = x;

linsys = linearize(sys);

sys.A
linsys.A
