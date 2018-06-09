
syms a b c
A = [3, 4, 5;
     2, 3, 4;
     a, b, c];
tic
A = symctrl.hess(A);
toc

simplify(A)
toc
