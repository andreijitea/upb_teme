function recoms = recommendations(path, liked_theme, num_recoms, min_reviews, num_features)
  % Get the best `num_recoms` recommandations similar with 'liked_theme'.

  % Incarca matricea din fisier
  mat = read_mat(path);

  % Proceseaza matricea
  mat = preprocess(mat, min_reviews);

  % Calculeaza svd
  [U, S, V] = svds(mat, num_features);

  % Sorteaza temele dupa similaritati
  [m, n] = size(V);
  aux = zeros(m, 1);

  for i = 1 : m
    aux(i) = cosine_similarity(V(i, :)', V(liked_theme, :)');
  end
  [~, sorted_ids] = sort(aux, 'descend');
  % Pe prima pozitie este liked_theme
  recoms = sorted_ids(2 : num_recoms + 1);
  recoms = recoms';
end
