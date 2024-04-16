% Computes the probability density function of the multivariate gaussian distribution.
function probabilities = multivariate_gaussian(X, mean_values, variances)
    % m - linii
    % n - coloane
    [m, n] = size(X);

    % Initializeaza vectorul de probabilitati
    probability = zeros(m, 1);

    % Calcularea fiecarei probabilitati
    % Pentru fiecare termen al vectorului
    for i = 1 : m
      probabilities(i, 1) = gaussian_distribution(X(i, :), mean_values, variances);
    endfor
endfunction
