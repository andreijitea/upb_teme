function [L] = cholesky (A)

	% Initializeaza variabilele necesare
	[n, n] = size(A);
	L = zeros(n);

	for j = 1:n
		% Calculeaza termenii de pe diagonala principala
		L(j,j) = sqrt(A(j,j));

		% Calculeaza termenii de pe coloana j, de sub diagonala
		L(j+1:n, j) = A(j+1:n, j) / L(j,j);
		
		% Actualizeaza minorul matricei A, de la A(j, j) -> A(n, n)
		A(j+1:n, j+1:n) = A(j+1:n, j+1:n) - L(j+1:n, j) * L(j+1:n, j)';
	end
endfunction
