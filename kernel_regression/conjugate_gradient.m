function [x] = conjugate_gradient (A, b, x0, tol, max_iter) 
  r = b - A * x0;
  v = r;
  x = x0;
  tol_sq = tol^2;
  k = 1;
  
  while k <= max_iter && norm(r)^2 > tol_sq
      t = (r' * r) / (v' * A * v);
      x = x + t * v;
      r = r - t * A * v;
      s = (r' * r) / (v' * v);
      v = r + s * v;
      k = k + 1;
  end
endfunction