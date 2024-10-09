function reduced_mat = preprocess(mat, min_reviews)
	[m, n] = size(mat);

	% Vector care memoreaza ce linii trebuie sterse
	removed_rows = false(m, 1);

	% Afla clientii care nu indeplinesc conditia
	for i = 1 : m
		contor = 0;
		for j = 1 : n
			if mat(i, j) ~= 0
				contor = contor + 1;
			end
		end
		if contor < min_reviews
			removed_rows(i) = true;
		end
	end

	% Proceseaza matricea redusa
	mat(removed_rows, :) = [];
	reduced_mat = mat;
end
