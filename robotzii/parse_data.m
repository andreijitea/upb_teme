function [x, y] = parse_data(filename)
	% file input format:
	% n
	% x0 x1 ... xn
	% y0 y1 ... yn

	% Deschide fisierul
	f = fopen(filename, 'r');

	% Citeste n
	n = fscanf(f, "%d", 1);
	% Citeste abscisele punctelor
	x = fscanf(f, "%d", n + 1);
	% Citeste ordonatele punctelor
	y = fscanf(f, "%d", n + 1);

	% Inchide fisierul
	fclose(f);

	% Transforma in vectori coloana
	x = x(:);
	y = y(:);
end