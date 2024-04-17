function [x] = conjugate_gradient (A, b, x0, tol, max_iter) 
  r = b - A * x0;
  v = r;
  x = x0;
  tolsquared = tol^2;
  k = 0;
  
  while k < max_iter && norm(r)^2 > tolsquared
      Av = A * v;
      alpha = (r' * r) / (v' * Av);
      x = x + alpha * v;
      r = r - alpha * Av;
      beta = (r' * r) / (v' * v);
      v = r + beta * v;
      k = k + 1;
  end
endfunction