function dV = lyapdiff(sys, V)
%LYAPDIFF Differentiate a given Lyapunov equation.
dV = gradient(V, sys.states)*reshape(sys.f, [], 1);

end

