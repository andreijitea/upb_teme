
function retval = distinct_words (tokens)
	% TODO: Find unique strings HINT: unique

	% Elimina termenii duplicat
	retval = unique(tokens);

	% Sorteaza alfabetic termenii
	retval = sort(retval);
endfunction
