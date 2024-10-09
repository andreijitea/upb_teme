function recoms = recommendations(path, liked_theme, num_recoms, min_reviews, num_features)
	% Incarca matricea din fisier
	mat = read_mat(path);

	% Proceseaza matricea
	mat = preprocess(mat, min_reviews);

	% Calculeaza svd
	[U, S, V] = svds(mat, num_features);

	% Transpune matricea de similaritati
	V = V';
	[m, n] = size(V);
	sim = zeros(n, 1);

	for i = 1 : n
		% Calculeaza similaritatea intre liked theme si tema curenta
		sim(i) = cosine_similarity(V(:, i), V(:, liked_theme));
	end
	% Sorteaza in ordine descrescatoare vectorul de similaritati
	[~, ids] = sort(sim, 'descend');
	% Pe prima pozitie este liked_theme
	recoms = ids(2 : num_recoms + 1)';
end
