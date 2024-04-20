% Implementarea functiei conform formulei din PDF
function retval = gaussian_kernel (x, y, sigma)
	numarator = norm(x-y, 2)^2;
	numitor = 2 * sigma^2;
	retval = exp(-numarator/numitor);
endfunction
