%% Firefly Synchronization Demo System
% Demo system showing firefly synchronization for 10 fireflies.
% 
% epsilon - synchronization threshold

syms epsilon

N = 10;

x = sym('x', [N, 1]);

sys = symhyss;
sys.states = x;

sys.cond(1, 1) = 1;
sys.cond(1, 2) = 1;
sys.cond(2, 1) = 1;

for k = 1:N
    sys.f(1, k) = 1;
    sys.cond(1, 2) = x(k) < 1 & sys.cond(1, 2);

    sys.f(2, k) = (1 + epsilon).*x(k) - (1 + epsilon).*x(k)*heaviside((1 + epsilon).*x(k) - 1);
    sys.cond(2, 1) = x(k) >= 1 & sys.cond(2, 1);
end

savedemo('fireflies', sys, {epsilon});
