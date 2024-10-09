function [P] = get_lower_inverse (L)
	% Initializeaza variabilele necesare
	[n, n] = size(L);
	P = eye(n);

	% Metoda Gauss-Jordan
	% Elimina termenii de sub diagonala principala
	for j = 1 : n-1
		for i = j+1 : n
				m = L(i,j) / L(j,j);
				P(i, :) = P(i,:) - m * P(j,:);
		endfor
	endfor

	% Imparte fiecare linie la termenul diagonalei principale
	for i = 1 : n
			P(i,:) = P(i,:) / L(i,i);

	endfor
endfunction
