function retval = word_idx (distinct_wds)
	% return the word_idx dictionary HINT: containers.Map

	% Lungimea listei date
	[m, ~] = length(distinct_wds);
	
	% Implementeaza un dictionar termen - indice
	retval = containers.Map(distinct_wds, 1 : m);
endfunction
