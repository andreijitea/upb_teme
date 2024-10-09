function y_interp = P_spline (coef, x, x_interp)
	% si(x)   = ai + bi(x - xi) + ci(x - xi)^2 + di(x - xi)^3, i = 0 : n - 1
	% coef = [a0, b0, c0, d0, a1, b1, c1, d1, ..., an-1, bn-1, cn-1, dn-1]
	% x = [x0, x1, ..., xn]
	% y_interp(i) = P_spline(x_interp(i)), i = 0 : length(x_interp) - 1

	y_interp = zeros(length(x_interp));
	
	for i = 0 : length(x_interp) - 1
		% Calculeaza intervalul in care se incadreaza x_interp(i + 1)
		j = find(x <= x_interp(i + 1), 1, 'last');
		if j > length(x) - 1
			j = length(x) - 1;
		end
		
		% Calculeaza valoarea pentru spline
		for k = 1 : 4
			y_interp(i + 1) = y_interp(i + 1) + coef(4 * (j - 1) + k) * (x_interp(i + 1) - x(j))^(k - 1);
		end
	end
end
