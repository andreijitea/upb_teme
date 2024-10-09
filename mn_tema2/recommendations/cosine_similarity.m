function similarity = cosine_similarity(A, B)
	% Calculeaza cosinusul unghiului dintre doi vectori.
	similarity = (A' * B) / (norm(A) * norm(B));
end
