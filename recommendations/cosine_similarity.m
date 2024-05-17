function similarity = cosine_similarity(A, B)
  % Compute the cosine similarity between two column vectors.
  similarity = (A' * B) / (norm(A) * norm(B));
end
