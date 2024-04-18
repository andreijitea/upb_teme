function [a] = get_prediction_params (K, y, lambda)
  [m, ~] = size(K);

  aux = lambda * eye(m) + K;

  L = cholesky(aux);
  L_inv = get_lower_inverse(L);

  aux_inv = L_inv' * L_inv;
  
  a = lambda * aux_inv * y;
endfunction
