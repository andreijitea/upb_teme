% Calculeaza probabilitatea pentru o linie a lui X
function probability = gaussian_distribution(X, mean_value, variance)
    % m - linii
    % n - coloane
    [m, n] = size(X);

    % Initializeaza variabilele necesare
    probability = 0;
    numarator = exp(((-1)/2) * (X(1, :) - mean_value) * inv(variance) *  (X(1, :) - mean_value)');
    numitor = ((2*pi)^(n/2) * det(variance^(1/2)));

    % Calculeaza probabilitatea unei linii a lui  X
    probability = numarator / numitor;

endfunction
