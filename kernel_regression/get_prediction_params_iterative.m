function [a] = get_prediction_params_iterative (K, y, lambda)
  # TO DO: folosind metode iterative, implementati logica
  # pentru a obtine vectorul coloana a, asa cum este descris in enuntul temei
  % K * a = y
  m = size(K, 1);
  a = zeros(m, 1);


  % Setează toleranța și numărul maxim de iterații
  tol = 1e-5;
  max_iter = 100;

  % Folosește metoda gradientului conjugat
  [a] = conjugate_gradient(K, y, a, tol, max_iter);
  %[a] = cgs(K, y);
endfunction
