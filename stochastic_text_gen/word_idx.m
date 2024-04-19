function retval = word_idx (distinct_wds)
    % return the word_idx dictionary HINT: containers.Map
    retval = containers.Map(distinct_wds, 1:length(distinct_wds));
endfunction
