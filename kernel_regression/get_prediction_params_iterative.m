function [a] = get_prediction_params_iterative (K, y, lambda)
  # TO DO: folosind metode iterative, implementati logica
  # pentru a obtine vectorul coloana a, asa cum este descris in enuntul temei
  % K * a = y
  m = size(K, 1);
  a = zeros(m, 1);


  % Setează toleranța și numărul maxim de iterații
  tol = 1e-5;
  max_iter = 2500;

  % Folosește metoda gradientului conjugat
  % Regularizarea matricei K
  A = K + lambda * eye(m);
  b = y;
  [a] = conjugate_gradient(A, b, a, tol, max_iter);
endfunction
