function y_interp = P_vandermonde (coef, x_interp)
	% P_vandermonde(x) = a0 + a1 * x + a2 * x^2 + ... + an * x^n
	% coef = [a0, a1, a2, ..., an]'
	% y_interp(i) = P_vandermonde(x_interp(i)), i = 0 : length(x_interp) - 1
	
	% Calculeaza dimensiuni necesare
	[m, ~] = size(coef);
	l = length(x_interp);
	% Initializeaza vectorul de iesire
	y_interp = zeros(l, 1);
	% Calculeaza fiecare element al vectorului
	for i = 0 : length(x_interp) - 1
		for j = 1 : m
			y_interp(i + 1) = y_interp(i + 1) + coef(j) * x_interp(i + 1).^(j - 1);
		end
	end
end
