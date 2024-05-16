function coef = vandermonde(x, y)
    % x = [x0, x1, ..., xn]'
    % y = [y0, y1, ..., yn]'
    % coef = [a0, a1, a2, ..., an]'

    [m, ~] = size(x);

    % Calculeaza matricea Vandermonde
    P = zeros(m);
    for i = 1 : m
        P(:, i) = x(:).^(i - 1);
    end
    % Calculeaza solutia sistemului
    coef = inv(P) * y;

endfunction
