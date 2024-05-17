function coef = spline_c2 (x, y)
	% Remember that the indexes in Matlab start from 1, not 0

	% si(x)   = ai + bi(x - xi) + ci(x - xi)^2 + di(x - xi)^3
	% si'(x)  =      bi         + 2ci(x - xi)  + 3di(x - xi)^2
	% si''(x) =                   2ci          + 6di(x - xi)

	[n, ~] = size(x);
	n = n - 1;
	A = zeros(4 * n);
	b = zeros(4 * n);

	b(1 : n + 1) = y(:);

	% si(xi) = yi, i = 0 : n - 1
	for i = 0 : n - 1
			A(i + 1, 4 * i + 1) = 1;
	end
	% s_n-1(xn) = yn
	for j = 1 : 4
		A(n + 1, 4 * (n - 1) + j) = (x(n + 1) - x(n))^(j - 1);
	end
	% si(x_i+1) = s_i+1(x_i+1), i = 0 : n - 1
	for i = 0 : n - 2
		for j = 1 : 4
			A(n + 2 + i, 4 * i + j) = (x(i + 2) - x(i + 1))^(j - 1);
			A(n + 2 + i, 4 * (i + 1) + j) =  - (x(i + 2) - x(i + 2))^(j - 1);
		end
	end
	% si'(x_i+1) = s_i+1'(x_i+1), i = 0 : n - 1
	for i = 0 : n - 2
		for j = 2 : 4
			A(2 * n + 1 + i, 4 * i + j) = (j - 1) * (x(i + 2) - x(i + 1))^(j - 2);
			A(2 * n + 1 + i, 4 * (i + 1) + j) =  - (j - 1) * (x(i + 2) - x(i + 2))^(j - 2);
		end
	end
	% si''(x_i+1) = s_i+1''(x_i+1), i = 0 : n - 1
	for i = 0 : n - 2
		for j = 3 : 4
			A(3 * n + i, 4 * i + j) = (j - 1) * (j - 2) * (x(i + 2) - x(i + 1))^(j - 3);
			A(3 * n + i, 4 * (i + 1) + j) =  - (j - 1) * (j - 2) * (x(i + 2) - x(i + 2))^(j - 3);
		end
	end
	% s0''(x0) = 0
	A(4 * n - 1, 4 * (n - 2) + 3) = 2;

	% s_n-1''(x_n) = 0
	for j = 3 : 4
		A(4 * n, 4 * (n - 1) + j) = (j - 1) * (j - 2) * (x(n + 1) - x(n))^(j - 3);
	end
	% Solve the system of equations
	coef = inv(A) * b;
	coef = coef(:,1);

end
