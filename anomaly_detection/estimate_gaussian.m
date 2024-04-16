% This function estimates the parameters of a Gaussian distribution using the data in X.
function [mean_values variances] = estimate_gaussian(X)
    % m = linii
    % n = coloane
    [m, n] = size(X);

    % Initializeaza variabilele necesare
    mean_values = zeros(1, n);
    variances = zeros(n, n);

    % Calcularea vectorului medie
    % Pentru fiecare termen al vectorului medie
    for i = 1 : n
      % Calculeaza suma termenilor lui X de pe coloana i
      sum = 0;
      for k = 1 : m
        sum = sum + X(k, i);
      endfor
      mean_values(i) = sum / m;
    endfor

    % Calcularea matricei de varianta
    % Pentru fiecare linie a lui X
    for i = 1 : m
      variances = variances + (X(i, :) - mean_values)' * (X(i, :) - mean_values);
    endfor
    variances = variances / m;
endfunction
