function retval = k_secv_idx (distinct_k_sec)
	% return disctionary containing the indices of each elem from distinct_k_sec 
	% HINT: containers.Map
	% Try not to set the key-value pairs iteratively, use containers.Map(keys, values) whenever possible

	% Lungimea listei date
	[n, ~] = length(distinct_k_sec)

	% Implementeaza un dictionar termen - indice
	retval = containers.Map(distinct_k_sec, 1 : n);
endfunction