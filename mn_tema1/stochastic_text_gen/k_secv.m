function B = k_secv (A, k)
	% given an array [a b a b c] and k=2
	% should return [ab ba ab bc]
	% HINT: use strjoin 

	% Lungimea listei date
	[m, ~] = length(A);

	% Initializeaza un array
	B = cell(m - k + 1, 1);

	% Calculeaza termenii array-ului
	for i = 1 : m - k + 1
		B(i) = strjoin(A(i : i + k - 1), ' ');
	end

	% Elimina ultimul termen al array-ului
	B(end) = [];
endfunction
