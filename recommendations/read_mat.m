function mat = read_mat(path)
	% Citeste matricea din fisier
	mat = csvread(path, 1, 1);
end
