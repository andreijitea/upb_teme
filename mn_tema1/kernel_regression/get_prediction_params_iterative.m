function [a] = get_prediction_params_iterative (K, y, lambda)
	# TO DO: folosind metode iterative, implementati logica
	# pentru a obtine vectorul coloana a, asa cum este descris in enuntul temei

	% Initializeaza variabilele necesare
	% K * a = y
	m = size(K, 1);
	a = zeros(m, 1);


	% Seteaza toleranta si numarul maxim de iteratii
	tol = 1e-5;
	max_iter = 2500;

	% Folosește metoda gradientului conjugat
	% Regularizarea matricei K
	A = K + lambda * eye(m);

	% Aplica functia gradientului conjugat
	[a] = conjugate_gradient(A, y, a, tol, max_iter);
endfunction
