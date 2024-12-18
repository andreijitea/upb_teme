% Implementarea functiei conform pseudocodului dat in pdf
function [x] = conjugate_gradient (A, b, x0, tol, max_iter) 
	r = b - A * x0;
	v = r;
	x = x0;
	tol_sq = tol^2;
	k = 1;
	
	while k <= max_iter && r' * r > tol_sq
		aux = A * v;
		t = (r' * r) / (v' * aux);
		x = x + t * v;
		r = r - t * aux;
		s = (r' * r) / (v' * v);
		v = r + s * v;
		k = k + 1;
	end
endfunction